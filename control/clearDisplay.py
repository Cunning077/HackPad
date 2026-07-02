import serial 
import time
ser = serial.Serial("/dev/ttyACM0", 115200)
time.sleep(2)
cmd = 0x02
packet = bytearray()
packet.append(cmd)
packet.append(2)
ser.write(packet)
print("Success")
