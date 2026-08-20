class Command:
    def __init__(self, cmd, data):
        self.cmd = cmd
        self.data = data

class SerialStatus:
    def __init__(self, status, dis_init):
        self.displays_init = dis_init
        self.status = status

commandList = {
        0x00 : {"Name": "Handshake", "Desc": "Initiates the handshake function to validate serial connection", "Use_Case": "internal"},
        0x01 : {"Name": "Handshake Ack", "Desc": "A cmd used in the handshake process to confirm handshake success", "Use_Case": "internal"},
        0x02 : {"Name": "Heartbeat", "Desc": "Cmd used to check if serial connection is still valid (pings arduino)", "Use_Case": "internal"},
        0x03 : {"Name": "Draw image", "Desc": "Sends and loads a image onto the selected tft display(See documentation for syntax and params)", "Use_Case": "ugen", "fillForm": ["imageLink", "display"]},
        0x04 : {"Name": "Clear display", "Desc": "Clears the selected display making it fully black", "Use_Case": "ugen", "fillForm": ["display"]},
        0x05 : {"Name": "Display test", "Desc": "Initiates a test on the selected display going through each color", "Use_Case": "ugen", "fillForm": ["display"]},
        0x06 : {"Name": "Draw text", "Desc": "Will display text in the requested coordinate point (will auto wrap)", "Use_Case": "ugen", "fillForm": ["text", "display"]},
        0x07 : {"Name": "Fill screen", "Desc": "fills selected display with chosen color", "Use_Case": "ugen", "fillForm": ["color", "display"]}
}
