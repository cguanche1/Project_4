#include <Stepper.h>
#include <ESP32Servo.h>

int stepsPerRev = 4096;

Stepper mystepper(stepsPerRev, 32,25,33,27);

Servo myServo;

int pos = 1;
int posStep = 1;

int servoPin = 13;

int stepCount = 0;
int turn = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(32, OUTPUT);
  pinMode(33, OUTPUT);
  pinMode(25, OUTPUT);
  pinMode(27, OUTPUT);
  

  pinMode(13, OUTPUT);

  pinMode(35, INPUT_PULLUP);

  pinMode(26, OUTPUT);
  
  myServo.setPeriodHertz(50);
  myServo.attach(servoPin);

  myServo.write(1);
}

void loop() {
  // put your main code here, to run repeatedly:
  mystepper.setSpeed(1);
  
  mystepper.step(1); //1/360th of a rev
  
  stepCount = (stepCount + 1) % 4096;

  delay(10);


  if(pos == 180){
    posStep = -1 * posStep;
  }
  if(pos == 0){
    posStep = -1 * posStep;
  }

  pos = pos + posStep;
  myServo.write(pos);

  if(digitalRead(35) == LOW){
    delay(15);
    if(digitalRead(35) == LOW){
      analogWrite(26, 125);
    }
  }

  if(digitalRead(35) == HIGH){
    delay(10);
    if(digitalRead(35) == HIGH){
      analogWrite(26, 0);
    }
  }
  
  
  /*
  if(stepCount == 4095){
    pos = pos + posStep;
    myServo.write(pos);
    if(pos == 180){
      posStep = posStep * -1;
    }
    if(pos == 0){
      posStep = posStep * -1;
    }
  }
  */
  //delay(5);
}
