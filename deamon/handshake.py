import time

class Handshake:
    def __init__(self, manager):
        self.manager = manager 
        self.displays = None
        self.buttons = None

    def perform(self):
        CMD_HANDSHAKE = 0x00
        CMD_HANDSHAKE_ACK = 0x01
        packet = bytearray()
        packet.append(CMD_HANDSHAKE)
        packet.append(0)
        self.manager.write(packet)
        print("cmd sent")
        time.sleep(2)
        

        response = self.manager.read(9)
        print(response)
        if response is None:
            return False
        if len(response) != 9:
            return False
        magic = response[0:4].decode("ascii")
        if magic != "MBRD":
            return False
        print("resp received")

        protocol = response[4]
        firmware_major = response[5]
        firmware_minor = response[6]
        self.displays = response[7]
        print(self.displays)
        self.buttons = response[8]
        if protocol != 1:
            return False
        
        packet = bytearray()
        packet.append(CMD_HANDSHAKE_ACK)
        self.manager.write(packet)

        response = self.manager.read(1)
        print("RESP:",response[0])
        if response is None or len(response) != 1:
            return False
        if response[0] != CMD_HANDSHAKE_ACK:
            return False
        print("Handshake Success")
        return True




