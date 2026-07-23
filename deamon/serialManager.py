from serial import Serial
from serial.tools import list_ports
import time

class SerialManager:
    def __init__(self):
        self.serial = None
        self.connected = None
        self.busy = False

    
    def get_ports(self):
        valid_ports = []
        for port in list_ports.comports():
            if port.device.startswith("/dev/ttyACM") or \
             port.device.startswith("/dev/ttyUSB"):
                valid_ports.append(port)
        return valid_ports  

    def connect(self, port):
        try:
            self.serial = Serial(port.device, baudrate=115200, timeout=1)
            time.sleep(3)
            self.connected = True
            return True
        except Exception:
            self.connected = False
            self.serial = None
            return False


    
    def disconnect(self):
        if self.serial is not None:
            try:
                self.serial.close()
            except Exception:
                pass
            self.serial = None

    def reconnect(self):
        for _ in range(5):
            self.disconnect()
            self.connect()
            if self.is_connected():
                return True
            time.sleep(1)
        self.serial = None
        return False

    def is_connected(self):
        return self.serial is not None and self.serial.is_open

    def write(self, data):
        if not self.is_connected():
            return False
        if self.busy:
            return False
        try:
            self.serial.write(data)
            self.serial.flush()
            return True
        except Exception:
            return self.reconnect()

    def read(self, size):
        if not self.is_connected():
            return None
        try:
            return self.serial.read(size)
        except Exception:
            return self.reconnect()

    def is_busy(self):
        return self.busy

    def begin_transaction(self):
        self.busy = True

    def end_transaction(self):
        self.busy = False


