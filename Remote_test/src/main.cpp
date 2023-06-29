#include <Arduino.h>

const int backward = 2;
const int left=3;
const int right=4;
const int forward=5;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(backward, OUTPUT);
  pinMode(left, OUTPUT);
  pinMode(right, OUTPUT);
  pinMode(forward, OUTPUT);


}

void loop() {
  //using serial write if the data is 1 then the car will move forward if the data is 2 then the car will move backward if the data is 3 then the car will move left if the data is 4 then the car will move right
  if(Serial.available()>0){
    int data=Serial.read();
    if(data==49){
      digitalWrite(forward, HIGH);
      digitalWrite(backward, LOW);
      digitalWrite(left, LOW);
      digitalWrite(right, LOW);
    }
    else if(data==50){
      digitalWrite(forward, LOW);
      digitalWrite(backward, HIGH);
      digitalWrite(left, LOW);
      digitalWrite(right, LOW);
    }
    else if(data==51){
      digitalWrite(forward, LOW);
      digitalWrite(backward, LOW);
      digitalWrite(left, HIGH);
      digitalWrite(right, LOW);
    }
    else if(data==52){
      digitalWrite(forward, LOW);
      digitalWrite(backward, LOW);
      digitalWrite(left, LOW);
      digitalWrite(right, HIGH);
    }
    else{
      digitalWrite(forward, LOW);
      digitalWrite(backward, LOW);
      digitalWrite(left, LOW);
      digitalWrite(right, LOW);
    }
    Serial.println(data);
  }
}
