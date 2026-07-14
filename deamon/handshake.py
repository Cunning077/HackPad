
class Handshake:
    def __init__(self, manager):
        self.manager = manager 

    def perform(self):
        print("Handshake Init")
        CMD_HANDSHAKE = 0x00
        CMD_HANDSHAKE_ACK = 0x01
        HANDSHAKE_SUCCESS = 1
        packet = bytearray()
        packet.append(CMD_HANDSHAKE)
        packet.append(0)
        self.manager.write(packet)
        print("cmd sent")

        response = self.manager.read(9)
        if response is None:
            return False
        if len(response) != 9:
            return False
        magic = response[0:4].decode("ascii")
        if magic != "MBRD":
            return False
        protocol = response[4]
        firmware_major = response[5]
        firmware_minor = response[6]
        displays = response[7]
        buttons = response[8]
        if protocol != 1:
            return False
        
        packet = bytearray()
        packet.append(CMD_HANDSHAKE_ACK)
        packet.append(HANDSHAKE_SUCCESS)
        self.manager.write(packet)

        response = self.manager.read(1)
        if response is None or len(response) != 1:
            return False
        if response[0] != 1:
            return False
        self.displays = displays
        self.buttons = buttons
        return True




