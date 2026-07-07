import serial
import time

import deps.colors as colors


ser = serial.Serial("/dev/ttyACM0", 115200)
time.sleep(2)
cmd = 0x05
packet = bytearray()
packet.append(cmd)
packet.append(0)
packet.extend(colors.GC9A01_BLUE.to_bytes(2, "big"))
ser.write(packet)
print("succes")
