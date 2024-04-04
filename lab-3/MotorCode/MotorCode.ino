#define MotorPin1 10 //OC2A
#define MotorPin2 11 //OC1A
#define MotorPin3 12 //OC1B
#define MotorPin4 13 //OC0A
//             0   1   2  3  4   5   6
int PWMs[] = {255,192,128,0,128,192,255};

void setup() {
  // put your setup code here, to run once:
  //setup pins
  pinMode(MotorPin1, OUTPUT);
  pinMode(MotorPin2, OUTPUT);
  pinMode(MotorPin3, OUTPUT);
  pinMode(MotorPin4, OUTPUT);

  CW(PWMs[3]); //run motor in clockwise direction
}

void loop() {
  // put your main code here, to run repeatedly:
  int motorIndex, speed;
  signed int stepDir;//stepDir is the direction of the step being taken,
               //eg. -1 for down, 0 for stationary, 1 for up
  if(motorIndex+stepDir > -1 && motorIndex+stepDir < 7){
    motorIndex=motorIndex+stepDir;
  }
  speed = PWMs[motorIndex];
  if(motorIndex < 3){
    CCW(speed);
  }
  else if(motorIndex > 3){
    CW(speed);
  }
  else if(motorIndex == 3){
    CW(speed);
  }
}

void CW(int speed){
    analogWrite(MotorPin1, speed);
    analogWrite(MotorPin2, 0);
    analogWrite(MotorPin3, speed);
    analogWrite(MotorPin4, 0);
}

void CCW(int motorIndex){
    analogWrite(MotorPin1, 0);
    analogWrite(MotorPin2, PWMs[motorIndex]);
    analogWrite(MotorPin3, 0);
    analogWrite(MotorPin4, PWMs[motorIndex]);
}