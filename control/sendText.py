import serial
import time
ser = serial.Serial("/dev/ttyACM0", 115200)
time.sleep(2)
packet = bytearray()
packet.append(0x04)
packet.append(0)
text = "Dont you love coding, Stardance is the funniest and coolest program out there:>)"
text_size = 2
char_width = 6 * text_size
char_height = 8 * text_size
text_width = len(text) * char_width
text_height = char_height
x = (240 - text_width) // 2
y = (240 - text_height) // 2
textLength = len(text)
packet.append(x)
packet.append(y)
packet.append(textLength)
packet.extend(text.encode("ascii"))
ser.write(packet)
print("Message Sent")
