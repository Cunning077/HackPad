from PIL import Image
from pathlib import Path
import serial
import time

ser = serial.Serial("/dev/ttyACM0", 115200)

time.sleep(2)

BASE_DIR = Path(__file__).parent
img = Image.open(BASE_DIR / "images" / "HP_IMG2.png")
img = img.convert("RGB")
length = 3 + (240 * 240 * 2)
packet = bytearray()
packet.append(0x01) 
packet.append(0)
packet.append(240)
packet.append(240)
packet.append(1)
print(packet)
ser.write(packet)
width, height = img.size
i = 0
for y in range(height):
    for x in range(width):
        r, g, b = img.getpixel((x, y))

        rgb565 = (
            ((r & 0xF8) << 8) |
            ((g & 0xFC) << 3) |
            (b >> 3)
        )
        i += 1

        ser.write(rgb565.to_bytes(2, 'big'))

print("Image sent")
print(i)
