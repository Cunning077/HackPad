from protocol import SerialStatus
from serialManager import SerialManager
from handshake import Handshake
from commands import Commands
from queues import firstStageQueue, secondStageQueue
import time

class Service:
    def __init__(self):
        self.serial = SerialManager()
        self.handshake = Handshake(self.serial)
        self.commands = Commands(self.serial, self.handshake)
        SerialStatus.display_init = False

    def run(self):
        while True:
            if not self.serial.is_connected():
                for port in self.serial.get_ports():
                    if not self.serial.connect(port):
                        time.sleep(1)

                    if self.handshake.perform():
                        print("MacroBoard Connected")
                        SerialStatus.display_init = False
                        time.sleep(4)
                        break
                    else:
                        self.serial.disconnect()
                        continue
            if self.serial.is_connected():
                if not SerialStatus.display_init:
                    self.commands.loadStartImages()
                    SerialStatus.display_init = True

        #adds continued functionality here like heartbeats and handling service commands etc

if __name__ == "__main__":
    service = Service()
    service.run()
