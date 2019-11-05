
#include <Stepper.h>
#include <ESP32Servo.h>

int stepsPerRev = 4096;

Stepper myStepper(stepsPerRev, 32,25,33,27);

int stepCount = 0;

Servo myServo;
int servoPin = 2;

int pos = 0;
int posStep = 1;

int firstStop = 60;
int secondStop = 120;

int joyX = 22;
int joyY = 21;
float maxL = 4095;
float maxR = 0;
float maxD = 0;
float maxU = 4095;

int buttPin = 35;

int rCol1 = 36;
int rCol2 = 39;
int rCol3 = 34;

int row1 = 14;
int row2 = 12;
int row3 = 13;

int col1 = 17;
int col2 = 16;
int col3 = 4;

int leadPin = 26;

int leds[3][3] = {{0,0,0},{0,0,0},{0,0,0}};

int INIT_TIME = 1000;
int CUR_TIME;

int FLASH = 100;

void setup() {
  pinMode(32,OUTPUT);
  pinMode(33,OUTPUT);
  pinMode(25,OUTPUT);
  pinMode(27,OUTPUT);

  pinMode(2,OUTPUT);
  
  pinMode(rCol1,INPUT_PULLUP);
  pinMode(rCol2,INPUT_PULLUP);
  pinMode(rCol3,INPUT_PULLUP);

  pinMode(row1,OUTPUT);
  pinMode(row2,OUTPUT);
  pinMode(row3,OUTPUT);
  digitalWrite(row1,HIGH);
  digitalWrite(row2,HIGH);
  digitalWrite(row3,HIGH);

  pinMode(col1,OUTPUT);
  pinMode(col2,OUTPUT);
  pinMode(col3,OUTPUT);
  digitalWrite(col1,LOW);
  digitalWrite(col2,LOW);
  digitalWrite(col3,LOW);

  pinMode(leadPin, OUTPUT);
  digitalWrite(leadPin, HIGH);

  myServo.setPeriodHertz(50);
  myServo.attach(servoPin);

  myServo.write(pos);

  CUR_TIME = INIT_TIME;
}

void loop() {
  setLights();

  digitalWrite(leadPin,LOW);
  
  while(pos < 60){
    if(digitalRead(joyX) <= maxR){
      if(pos != 0){
        pos = pos - 1;
        myServo.write(pos);
        delay(5);
      }
    }
    if(digitalRead(joyX) >= maxL){
      pos = pos + 1;
      myServo.write(pos);
      delay(5);
    }
    if(digitalRead(joyY) >= maxU){
      myStepper.step(1);
      delay(10);
    }
    if(digitalRead(joyY) <= maxD){
      myStepper.step(-1);
      delay(10);
    }

    if(digitalRead(rCol1) != HIGH || digitalRead(rCol2) != HIGH ||
      digitalRead(rCol3) != HIGH){
        flashCol(1);
        reset();
        break;
    }
  }

  while(pos >= 60 && pos < 120){
    if(digitalRead(joyX) <= maxR){
      if(pos != 60){
        pos = pos - 1;
        myServo.write(pos);
        delay(5);
      }
    }
    if(digitalRead(joyX) >= maxL){
      pos = pos + 1;
      myServo.write(pos);
      delay(5);
    }
    if(digitalRead(joyY) >= maxU){
      myStepper.step(1);
      delay(10);
    }
    if(digitalRead(joyY) <= maxD){
      myStepper.step(-1);
      delay(10);
    }

    if(digitalRead(rCol1) != HIGH || digitalRead(rCol2) != HIGH ||
      digitalRead(rCol3) != HIGH){
        flashCol(2);
        reset();
        break;
    }
  }

  while(pos >= 120 && pos < 150){
    if(digitalRead(joyX) <= maxR){
      if(pos != 120){
        pos = pos - 1;
        myServo.write(pos);
        delay(5);
      }
    }
    if(digitalRead(joyX) >= maxL){
      pos = pos + 1;
      myServo.write(pos);
      delay(5);
    }
    if(digitalRead(joyY) >= maxU){
      myStepper.step(1);
      delay(10);
    }
    if(digitalRead(joyY) <= maxD){
      myStepper.step(-1);
      delay(10);
    }

    if(digitalRead(rCol1) != HIGH || digitalRead(rCol2) != HIGH ||
      digitalRead(rCol3) != HIGH){
        flashCol(3);
        reset();
        break;
      }
  }

  if(pos == 150){
    flashCol(1);
    flashCol(2);
    flashCol(3);
    reset();
  }

}

void setLights(){
  int light = int(random(0,3));
  if(light != 0 && light != 1 && light != 2){
    light = 2;
  }

  digitalWrite(col1,HIGH);

  setCol(light,1);

  delay(CUR_TIME);

  digitalWrite(col1,LOW);
  digitalWrite(col2,HIGH);

  light = int(random(0,3));
  if(light != 0 && light != 1 && light != 2){
    light = 1;
  }

  setCol(light,2);

  delay(CUR_TIME);

  digitalWrite(col2,LOW);
  digitalWrite(col3,HIGH);

  light = int(random(0,3));
  if(light != 0 && light != 1 && light != 2){
    light = 0;
  }

  setCol(light,3);

  delay(CUR_TIME);

  digitalWrite(col3,LOW);
  digitalWrite(row1,HIGH);
  digitalWrite(row2,HIGH);
  digitalWrite(row3,HIGH);
}

void setCol(int light,int col){
  if(light != 0){
    digitalWrite(row1,LOW);
    leds[col-1][0] = 1;
  }
  if(light != 1){
    digitalWrite(row2,LOW);
    leds[col-1][1] = 1;
  }
  if(light != 2){
    digitalWrite(row3,LOW);
    leds[col-1][2] = 1;
  }
}

void flashCol(int col){
  if(col == 0){
    digitalWrite(col1, HIGH);
  }
  if(col == 1){
    digitalWrite(col2, HIGH);
  }
  if(col == 2){
    digitalWrite(col3, HIGH);
  }

  for(int i = 0; i < FLASH; i++){
    digitalWrite(row1, LOW);
    delay(5);
    digitalWrite(row1,HIGH);
    digitalWrite(row2,LOW);
    delay(5);
    digitalWrite(row2,HIGH);
    digitalWrite(row3,LOW);
    delay(5);
    digitalWrite(row3,HIGH);
  }

  if(col == 0){
    digitalWrite(col1, LOW);
  }
  if(col == 1){
    digitalWrite(col2, LOW);
  }
  if(col == 2){
    digitalWrite(col3, LOW);
  }
  
}

void reset(){
  digitalWrite(col1, LOW);
  digitalWrite(col2, LOW);
  digitalWrite(col3, LOW);

  digitalWrite(row1, HIGH);
  digitalWrite(row2, HIGH);
  digitalWrite(row3, HIGH);

  pos = 0;
  myServo.write(pos);

}
