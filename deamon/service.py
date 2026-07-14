from deamon.protocol import SerialStatus
from serialManager import SerialManager
from handshake import Handshake
import time

class Service:
    def __init__(self):
        self.serial = SerialManager()
        self.handshake = Handshake(self.serial)

    def run(self):
        print("called")
        while True:
            if not self.serial.is_connected():
                for port in self.serial.get_ports():
                    print(f"Trying {port.device}")
                    if not self.serial.connect(port):
                        time.sleep(1)
                        continue
                    if self.handshake.perform():
                        print("MacroBoard Connected")
                        time.sleep(1)
                        break
                        
                    self.serial.disconnect()
                    SerialStatus.display_init = False 
            if not SerialStatus.display_init:
                loadStartImages()
                SerialStatus.display_init = True
            if not commandQueue.empty():
                cmd = commandQueue.pop()
                resolveCMD(cmd)
        #adds continued functionality here like heartbeats and handling service commands etc

if __name__ == "__main__":
    service = Service()
    service.run()
