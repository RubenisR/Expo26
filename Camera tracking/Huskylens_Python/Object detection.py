from huskylib import HuskyLensLibrary as huskylens
import numpy as np
import serial
import json
import time

h1 = huskylens("SERIAL", "COM7")  # Serial port PC
# hl = HuskyLensLibrary("I2C","", address=0x32,channel=0) # I2C raspeberry pi
print("Checking if camera is working: {}".format(h1.knock()))
h1.algorthim("ALGORITHM_TAG_RECOGNITION")


def printObjectNicely(obj):
    count = 1
    if type(obj) == list:
        for i in obj:
            print(
                "\t "
                + ("BLOCK_" if i.type == "BLOCK" else "ARROW_")
                + str(count)
                + " : "
                + json.dumps(i.__dict__)
            )
            count += 1
    else:
        print(
            "\t "
            + ("BLOCK_" if obj.type == "BLOCK" else "ARROW_")
            + str(count)
            + " : "
            + json.dumps(obj.__dict__)
        )


while True:
    a = h1.count()
    if a == 1:
        printObjectNicely(h1.getObjectByID(1))
    else:
        print("No object detected")
    # printObjectNicely(h1.getObjectByID(1))
    # delay by 1 second
    # time.sleep(1)
