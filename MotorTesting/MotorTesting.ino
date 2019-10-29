#include <Stepper.h>
#include <ESP32Servo.h>

int stepsPerRev = 2048;

Stepper mystepper(stepsPerRev, 32,33,25,26);

Servo myServo;

int pos = 0;
int posStep = 10;

int servoPin = 13;

int stepCount = 0;

void setup() {
  // put your setup code here, to run once:

  myServo.setPeriodHertz(50);
  myServo.attach(servoPin);

  myServo.write(0);
}

void loop() {
  // put your main code here, to run repeatedly:
  //mystepper.setSpeed(50);
  
  mystepper.step(1); //1/360th of a rev
  
  stepCount = (stepCount + 1) % 2048;

  delay(5);


  
  if(stepCount == 2047){
    pos = pos + posStep;
    myServo.write(pos);
    if(pos == 180){
      posStep = posStep * -1;
    }
    if(pos == 0){
      posStep = posStep * -1;
    }
  }
  //delay(5);
}
