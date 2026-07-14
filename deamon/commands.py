from PIL import Image
from pathlib import Path
import serial
import time

from handshake import Handshake
from protocol import Command

class Commands:
    def __init__(self):
        self.base_dir = Path(__file__).parent

    def loadStartImages():
        for display in range(Handshake.displays):
            img_filename = f"DISP{display}_IMG"
            cmd = Command(0x03, display, img_filename)
            commandQueue.push(cmd)

    def sendImages(cmd):
        




