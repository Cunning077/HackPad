class Command:
    def __init__(self, cmd, display, data):
        self.cmd = cmd
        self.display = display
        self.data = data

class SerialStatus:
    def __init__(self, status, dis_init):
        self.displays_init = dis_init
        self.status = status
