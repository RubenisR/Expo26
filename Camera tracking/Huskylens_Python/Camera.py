from huskylib import HuskyLensLibrary
import serial

h1 = HuskyLensLibrary("SERIAL", "COM7")  # Serial port PC
# hl = HuskyLensLibrary("I2C","", address=0x32,channel=0) # I2C raspeberry pi
print(h1.knock())
