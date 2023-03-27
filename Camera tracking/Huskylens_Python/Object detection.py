from huskylib import HuskyLensLibrary
from huskylib import Block
import serial

h1 = HuskyLensLibrary("SERIAL", "COM7")  # Serial port PC
# hl = HuskyLensLibrary("I2C","", address=0x32,channel=0) # I2C raspeberry pi
print("Checking if camera is working: {}".format(h1.knock()))
# call ID from class Block
print("ID: {}".format(Block.ID))
