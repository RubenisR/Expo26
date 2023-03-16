from huskylib import HuskyLensLibrary

h1 = HuskyLensLibrary("SERIAL", "/dev/ttyUSB0")
print(h1.knock())
