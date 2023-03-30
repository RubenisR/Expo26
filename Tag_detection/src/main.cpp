#include <Arduino.h>
#include "HUSKYLENS.h"
// #include "PIDLoop.h"

// PIDLoop headingLoop(120, 0, 0, false);
HUSKYLENS huskylens; // create hsukylens object
int ID1 = 1;         // ID of the first tag

void printResult(HUSKYLENSResult result)
{
  if (result.command == COMMAND_RETURN_BLOCK)
  {
    Serial.println(String() + F("Block:xCenter=") + result.xCenter + F(",yCenter=") + result.yCenter + F(",width=") + result.width + F(",height=") + result.height + F(",ID=") + result.ID);
  }
  else
  {
    Serial.println("Object unknown!");
  }
  delay(1000);
}

void setup()
{
  Serial.begin(9600);
  Wire.begin(); // begins comunication with the HUSKYLENS
  while (!huskylens.begin(Wire))
  {
    Serial.println(F("Begin failed!"));
    Serial.println(F("1.Please recheck the \"Protocol Type\" in HUSKYLENS (General Settings>>Protol Type>>I2C)"));
    Serial.println(F("2.Please recheck the connection."));
    delay(100);
  }
  huskylens.writeAlgorithm(ALGORITHM_TAG_RECOGNITION); // set the algorithm to tag recognition
}

void loop()
{
  // int32_t error;
  if (!huskylens.request(ID1))
  { // cannot request data from the HUSKYLENS
    Serial.println("check connection to camera");
  }
  else if (!huskylens.isLearned()) // if object has not been learned
  {
    Serial.println("No Object learned");
  }
  else if (!huskylens.available()) // if no object is detected
  {
    Serial.println("No Object detected");
  }
  else
  {
    HUSKYLENSResult result = huskylens.read(); // read the result
    printResult(result);                       // print the result
    // error = (int32_t)result.xTarget - (int32_t)160; // Calculate the tracking error
    // headingLoop.update(error);
  }
}