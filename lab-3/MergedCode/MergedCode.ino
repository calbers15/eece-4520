#include <LiquidCrystal.h>
#include <Wire.h>
#include <RTClib.h>

#define rs 25
#define en 23
#define d0 36
#define d1 34
#define d2 32
#define d3 30
#define d4 28
#define d5 26
#define d6 24
#define d7 22

#define MotorPin1 10
#define MotorPin2 11

RTC_DS1307 clock;

//             0   1   2  3  4   5   6
int PWMs[] = {255,192,128,0,128,192,255};
volatile char dir[] = "N/A";
int speed;
LiquidCrystal lcd(rs,en,d0,d1,d2,d3,d4,d5,d6,d7);


void setup() {
  // put your setup code here, to run once:
    cli();//stop interrupts

  //set timer1 interrupt at 1Hz
  TCCR1A = 0;// set entire TCCR1A register to 0
  TCCR1B = 0;// same for TCCR1B
  TCNT1  = 0;//initialize counter value to 0
  // set compare match register for 1hz increments
  OCR1A = 15624;// = (16*10^6) / (1*1024) - 1 (must be <65536)
  // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  // Set CS12 and CS10 bits for 1024 prescaler
  TCCR1B |= (1 << CS12) | (1 << CS10);  
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);

  sei();//allow interrupts
  while(!clock.begin()){delay(1);}//setup RTC, is a few seconds off though
  clock.adjust(DateTime(F(__DATE__), F(__TIME__)));
  Serial.begin(9600);//debug
  Serial.print("RTC connected\n");
  lcd.begin(16, 2);
  lcd.print("");

  //delay(100);
  //sei();//stop interrupts

  
  Serial.print("interrupt setup\n");
  pinMode(MotorPin1, OUTPUT);
  pinMode(MotorPin2, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int motorIndex=5;
  signed int stepDir=0;//stepDir is the direction of the step being taken,
               //eg. -1 for down, 0 for stationary, 1 for up. For debug =0
  
  if(motorIndex+stepDir > -1 && motorIndex+stepDir < 7){
    motorIndex=motorIndex+stepDir;
  }
  speed = PWMs[motorIndex];
    if(motorIndex < 3){
    analogWrite(MotorPin2, speed);
    analogWrite(MotorPin1, 0);
    dir[0]='C';
    dir[1]='C';
    dir[2]='W';
  }
  else if(motorIndex > 3){
    analogWrite(MotorPin1, speed);
    analogWrite(MotorPin2, 0);
    dir[0]='C';
    dir[1]='W';
    dir[2]=' ';
  }
  else if(motorIndex == 3){
    analogWrite(MotorPin1, 0);
    analogWrite(MotorPin2, 0);
    dir[0]='N';
    dir[1]='/';
    dir[2]='A';
  }

}

ISR(TIMER1_COMPA_vect){//timer1 interrupt 1Hz toggles pin 13 (LED)
//generates pulse wave of frequency 1Hz/2 = 0.5kHz (takes two cycles for full wave- toggle high then toggle low)
  sei();
  lcd.setCursor(0,0);
  lcd.print(speed);
  lcd.print(dir[0]);
  lcd.print(dir[1]);
  lcd.print(dir[2]);
  
  DateTime RTCdata = clock.now();
  lcd.setCursor(3,2);
  lcd.print(RTCdata.hour());

  lcd.print(':');

  lcd.setCursor(6,2);
    if(RTCdata.minute()<10){
    lcd.print('0');
    lcd.print(RTCdata.minute());
  }
  else{lcd.print(RTCdata.minute()); }

  lcd.setCursor(8,2);
  lcd.print(":");
  if(RTCdata.second()<10){
    lcd.print('0');
    lcd.print(RTCdata.second());
  }
  else{lcd.print(RTCdata.second()); }
  cli();
}
