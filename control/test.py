import serial
import time
ser = serial.Serial("/dev/ttyACM0", 115200)
time.sleep(2)
cmd = 0x03
packet = bytearray()
packet.append(cmd)
packet.append(0)
ser.write(packet)
print("Success")

