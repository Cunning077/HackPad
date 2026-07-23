from PIL import Image
from pathlib import Path
from queues import firstStageQueue, secondStageQueue
import serial
import time

from handshake import Handshake
from protocol import Command
import time

class Commands:
    def __init__(self, manager, handshake):
        self.base_dir = Path(__file__).parent
        self.manager = manager
        self.handshake = handshake


    def loadStartImages(self):
        rotation = 1
        print("BUFFER BEFORE IMAGE:", self.manager.serial.in_waiting)
        for display in range(self.handshake.displays):
            print("Disp: ", display)
            img_filename = f"DISP{display}_IMG.png"
            packet = bytearray()
            packet.append(0x03)
            packet.append(0)
            self.manager.write(packet)
            img = Image.open(self.base_dir / "images" / img_filename)
            img = img.convert("RGB")
            width, height = img.size
            pixels = img.load()
            while True:
                response = self.manager.read(1)
                print(response)
                if response is None:
                    return
                if len(response) != 1:
                    return
                if response[0] != 0x03:
                    return
                print("resp received")

                packet = bytearray()
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
                            print("buffer sent")
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


                




        




