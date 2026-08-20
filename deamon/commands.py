from PIL import Image
from pathlib import Path
import time

from protocol import Command, commandList
from colors import Colors


class Commands:
    def __init__(self, manager, handshake, firstQueue, secondQueue):
        self.base_dir = Path(__file__).parent
        self.manager = manager
        self.handshake = handshake
        self.firstStageQueue = firstQueue
        self.secondStageQueue = secondQueue


    def loadStartImages(self):
        rotation = 1
        print("BUFFER BEFORE IMAGE:", self.manager.serial.in_waiting)
        for display in self.handshake.displays:
            print("Disp: ", display)
            img_filename = f"DISP{display}_IMG.png"
            packet = bytearray()
            packet.append(0x03)
            packet.append(0) #filler for cmdId
            self.manager.write(packet)
            response = self.manager.read(1) #toss one reply for queue confirmation 
            print(response)
            img = Image.open(self.base_dir / "images" / img_filename)
            img = img.convert("RGB")
            width, height = img.size
            pixels = img.load()
            while True:
                response = self.manager.read(2)
                print(response)
                if response is None:
                    return
                if len(response) != 2:
                    return
                if response[0] != 0x03:
                    return
                print("resp received")

                packet = bytearray()
                packet.append(display)
                packet.append(width)
                packet.append(height)
                packet.append(rotation)
                self.manager.write(packet)
                print("Details sent")
                bytesSent = 0
                buffer = bytearray()
                for y in range(height):
                    for x in range(width):
                        r, g, b = pixels[x, y]
                        rgb565 = (
                            ((r & 0xF8) << 8) |
                            ((g & 0xFC) << 3) |
                             (b >> 3)
                        )
                        buffer.extend(rgb565.to_bytes(2, "big"))
                        bytesSent += 2
                        if len(buffer) >= 48:
                            self.manager.write(buffer)
                            buffer.clear()
                            time.sleep(0.1)
                time.sleep(0.2)
                if buffer:
                    self.manager.write(buffer)
                    buffer.clear()
                print(f"Bytes sent: {bytesSent}")
                while True:
                    response = self.manager.read(1)
                    print(response)
                    if response is None:
                        return
                    if len(response) != 1:
                        return
                    if response[0] != 0x03:
                        return
                    print("Cmd confirmed done")
                    break
                break


    def receiveCommands(self):
        # for now since there is no gui i will prompt the user if they want to do new cmd
        resp = input("Attempt any commands? (y/n): ").lower()
        if resp == "y":
            while True:
                choice = input("What command would you like? ('M' for menu / 'C' to cancel): ")
                if choice.lower() == "m":
                    for cmd_id, cmd in commandList.items():
                        if cmd["Use_Case"] == "ugen":
                            print(f"{cmd['Name']}: {cmd['Desc']} | {cmd_id:#04x}")
                    continue
                if choice.lower() == "c":
                    print("Selection cycle canceled")
                    return None
                try:
                    cmd_id = int(choice, 16)  
                except ValueError:
                    print("Not a valid command.")
                    continue
                if cmd_id in commandList:
                    fillForm = commandList[cmd_id]["fillForm"]
                    data = {}
                    print("fill this:")
                    for form in fillForm:
                        rec = input(f"{form}:")
                        data[form] = rec
                    print(type(cmd_id))
                    cmd = Command(cmd_id, data)
                    print(cmd)
                    return cmd
                print("Not a valid request.")
        elif resp == "n":
            print("Selection cycle skipped")
            return None            

    def readIncoming(self):
        timeout = 3
        start = time.monotonic()
        while time.monotonic() - start < timeout:
            response = self.manager.read(2)
            if response:
                return response
            time.sleep(0.01)
        return None

    def resolveFirstStageCmd(self):
        command = self.firstStageQueue.pop() 
        self.manager.busy = True
        curId = self.secondStageQueue.getCurId()
        packet = bytearray()
        packet.append(command.cmd)
        packet.append(curId)
        self.manager.write(packet)
        response = self.manager.read(1)
        print("response:")
        print(response)
        if response is None:
            self.firstStageQueue.push(command) #reinstate it to queue
            print("push bad")
            return
        if len(response) != 1:
            self.firstStageQueue.push(command)
            print("push bad")
            return
        if response[0] != command.cmd:
            print("push bad")
            self.firstStageQueue.push(command)
            return
        #at this point the command was received and i need to push it to secondstage
        self.secondStageQueue.addCMD(command)
            


        #here i want to sample pop whatever cmd is at the top of the firstStageQueue during a time when the serial isnt busy on either end i need confirmation from the arduino its been received to get success

    def resolveCMD(self, receivedBit):
        """
        if receivedBit == 0x02:
            #heartbeatCommand
        """
        cmd = self.secondStageQueue.popCMD(receivedBit[1])
        if cmd:
            match cmd.cmd:
                case 0x03:
                    self.manager.busy = True
                    #unpack data (image and display)
                    img_filename = cmd.data["imageLink"]
                    display = int(cmd.data["display"])
                    if self.displayImage(img_filename, display):
                        return
                    print("Image CMD Failed")
                    self.manager.busy = False
                    #Send over to displayImage
                case 0x04:
                    self.manager.busy = True
                    display = int(cmd.data["display"])
                    if self.clearDisplay(display):
                        return
                    print("Clear Display CMD Failed")
                    self.manager.busy = False
                    #clear display contains display requested
                case 0x05:
                    self.manager.busy = True
                    display = int(cmd.data["display"])
                    if self.displayTest(display):
                        return
                    print("Display Test CMD Failed")
                    self.manager.busy = False
                    #display test contains display
                case 0x06:
                    self.manager.busy = True
                    text = cmd.data["text"]
                    display = int(cmd.data['display'])
                    if self.writeText(text, display):
                        return
                    print("Write Text CMD Failed")
                    self.manager.busy = False
                    #display text contains text,display and location (x,y)
                case 0x07:
                    self.manager.busy = True
                    color = cmd.data["color"]
                    display = int(cmd.data["display"])
                    if self.fillScreen(display, color):
                        return
                    print("Fill Screen CMD Failed")
                    self.manager.busy = False
                    #fill screen contains color and display
                case _:
                    print("No Command Found")
                    print(f"CMD: {cmd['cmd']}")
                    return
                    #unknown cmd shouldnt ever happen


    def displayImage(self, img_filename, display):
        rotation = 1
        packet = bytearray()
        packet.append(0x03)
        packet.append(display)
        self.manager.write(packet)
        img = Image.open(self.base_dir / "images" / img_filename)
        img = img.convert("RGB")
        width, height = img.size()
        pixels = img.load()

        response = self.manager.read(1)
        if response is None:
            return False
        if len(response) != 1:
            return False
        if response[0] != 0x03:
            return False
        
        packet = bytearray()
        packet.append(width)
        packet.append(height)
        packet.append(rotation)
        self.manager.write(packet)
        buffer = bytearray()
        for y in range(height):
            for x in range(width):
                r,g,b = pixels[x,y]
                rgb565 = (
                    ((r & 0xF8) << 8) |
                    ((g & 0xFC) << 3) |
                    (b >> 3)
                )
                buffer.extend(rgb565.to_bytes(2, "big"))
                if len(buffer) >= 48:
                    self.manager.write(buffer)
                    buffer.clear()
                    time.sleep(0.1)
        time.sleep(0.2)
        if buffer:
            self.manager.write(buffer)
            buffer.clear()
        while True:
            response = self.manager.read(1)
            if response is None:
                return False
            if len(response) != 1:
                return False
            if response[0] != 0x03:
                return False
            return True
                    
    def clearDisplay(self, display):
        packet = bytearray()
        packet.append(display)
        self.manager.write(packet)
        return True

    def displayTest(self, display):
        packet = bytearray()
        packet.append(display)
        self.manager.write(packet)
        return True

    def writeText(self, text, display):
        packet = bytearray()
        packet.append(display)
        text_size = 2
        text_length = len(text)
        text_width = text_length * (6 * text_size)
        text_height = 8 * text_size
        x = (240 - text_width) // 2
        y = (240 - text_height) // 2
        packet.append(x)
        packet.append(y)
        packet.append(text_length)
        packet.extend(text.encode("ascii"))
        self.manager.write(packet)
        return True

    def fillScreen(self, display, selColor):
        packet = bytearray()
        packet.append(display)
        packet.extend(getattr(Colors, selColor).to_bytes(2, "big"))
        self.manager.write(packet)
        return True


                




        




