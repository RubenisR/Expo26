from huskylib import HuskyLensLibrary

h1 = HuskyLensLibrary("SERIAL", "/dev/ttyUSB0", 3000000)  # Serial port PC
# hl = HuskyLensLibrary("I2C","", address=0x32,channel=0) # I2C raspeberry pi
print(h1.knock())
