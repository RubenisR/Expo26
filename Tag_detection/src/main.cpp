#include <Arduino.h>
#include "HUSKYLENS.h"

// 1st wheel
const int ena =  7;
const int in1 =  6;
const int in2 =  5;
bool enable_in1 = 1;
bool enable_in2 = 0;
int power_a = 0;
int power_b = 0;


// 2nd wheel
const int enb =  8;
const int in3 =  9;
const int in4 = 10;
bool enable_in3 = 1;
bool enable_in4 = 0;

long int time = 0;
int movement_direction;
int movement = 0;
long int indicator = 0;


HUSKYLENS huskylens; // create hsukylens object
int ID1 = 1;         // ID of the first tag
int x;
int y;
int w;
int h;
float distance =0;
float d;
void printResult(HUSKYLENSResult result)
{
  if (result.command == COMMAND_RETURN_BLOCK)
  {
    // Serial.println(String() + F("Block:xCenter=") + result.xCenter + F(",yCenter=") + result.yCenter + F(",width=") + result.width + F(",height=") + result.height + F(",ID=") + result.ID);
    x = result.xCenter;
    y = result.yCenter;
    w = result.width;
    h = result.height;
  }
  else
  {
    Serial.println("Object unknown!");
  }
  delay(1000);
}

int objectlocation()
{ // if object is to the right or left then move back to center
  int position = x;
  if (position < 130)
  {
    Serial.println("object left");
    return 0;
  }
  else if (position > 190)
  {
    Serial.println("object right");
    return 2;
  }
  else if ((position >= 130) && (position <= 190))
  {
    Serial.println("object centered");
    return 1;
  }
  else return -1;
}

void move(){
  if (d<145){
    Serial.println("move backward");
  }
  else if (d>155){
    Serial.println("move forward");

  }
  else if (d>145 && d<155){
    Serial.println("centered");
  }
  else{
    Serial.println("error");
  }
  
}

float calculation(int h)
{
  distance = -2.85726 * h + 281.9097;
  return distance;
}


void setup()
{
  
  Serial.begin(9600);
  Wire.begin(); // begins comunication with the HUSKYLENS
  pinMode(ena, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);

  pinMode(enb, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);


  while (!huskylens.begin(Wire))
  {
    Serial.println(F("Begin failed!"));
    Serial.println(F("1.Please recheck the \"Protocol Type\" in HUSKYLENS (General Settings>>Protol Type>>I2C)"));
    Serial.println(F("2.Please recheck the connection."));
    delay(100);
  }
  huskylens.writeAlgorithm(ALGORITHM_TAG_RECOGNITION); // set the algorithm to tag recognition

  movement_direction = -1;
  time = millis();
}

void loop()
{

//delay(2000);

  /*digitalWrite(in1,enable_in1);
  digitalWrite(in2,enable_in2);
  digitalWrite(in3, enable_in3);
  digitalWrite(in4,enable_in4);
  analogWrite(ena, 255);
  analogWrite(enb, 255);
  delay(2000);
  enable_in1 = 0;
  enable_in3 = 0;*/
  
  /*
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
  }
  Serial.println(calculation(h));
  d=calculation(h);
  */
  if (((millis() - time) > 100))
  {

    if (!huskylens.request(ID1))
     { // cannot request data from the HUSKYLENS
      Serial.println("check connection to camera");
      movement_direction = -1;
      }
    else if (!huskylens.isLearned()) // if object has not been learned
     {
       Serial.println("No Object learned");
       movement_direction = -1;
     }
    else if (!huskylens.available()) // if no object is detected
      {
        //Serial.println("No Object detected");
        movement_direction = -1;
      }
    else
    {
        HUSKYLENSResult result = huskylens.read(); // read the result
        printResult(result);                       // print the result
        //Serial.println(calculation(h));

        d=calculation(h);
        movement_direction = objectlocation();
        Serial.println(movement_direction);
        Serial.println(x);
    }
    Serial.println(movement_direction);
    time = millis();
    movement = 0;
  }
  else 
  {
      if (movement_direction == -1)
       {
          enable_in1 = 0;
          enable_in3 = 0;
          power_a = 0;
          power_b = 0;
      }
      else if (movement_direction == 0)
       {
          enable_in1 = 1;
           enable_in3 = 1;
           power_a = 255;
           power_b = 127;
       }
       else if (movement_direction == 1)
       {
           enable_in1 = 1;
          enable_in3 = 1;
          power_a = 255;
          power_b = 255;
       }
       else if (movement_direction == 2)
        {
          enable_in1 = 1;
          enable_in3 = 1;
          power_a = 127;
          power_b = 255;
         }
        movement = 1;
  }

  if (movement == 1)
  {
  digitalWrite(in1,enable_in1);
  digitalWrite(in2,enable_in2);
  digitalWrite(in3, enable_in3);
  digitalWrite(in4,enable_in4);
  analogWrite(A1, power_a);
  analogWrite(A2, power_b);
  }
  
 
  //move();

  // delay(1000);
  //Serial.println(x);
  //Serial.println(y);
  // Serial.print("width");
  // Serial.println(w);
  // Serial.print("height");
  //Serial.println(h);

  // objectlocation();
}