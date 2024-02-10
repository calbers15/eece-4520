//#include "TimerSample.ino"
#define GREEN 55 //assigning pins specific values without using globals
#define YELLOW 54
#define RED 53
#define BUZZER 2
#define Button 52
#define GREEN_LEFT_ARROW 51

void setup() {
  // put your setup code here, to run once:

  
  pinMode(GREEN, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  pinMode(RED, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(Button, INPUT);
  pinMode(GREEN_LEFT_ARROW, OUTPUT);

  while(digitalRead(Button) == LOW)
  {
    RedFlashing();
  }
}

void loop() {
  
  // put your main code here, to run repeatedly:

  //some code to make red light flash 1-1 for 3 sec
  //some function to buzz the buzzer
  
  //some for loop for GLA to be solid for 3 seconds
  
  //some for loop for flahsing GLA for 3 seconds (on 1 sec-off 1 sec(aka 1-1))
  //some function to buzz the buzzer

  //some code to make green light stay solid for 9 seconds

  //some code to make green light flash 1-1 for 3 seconds
  //some function to buzz the buzzer
  
  //some code to make yellow light solid for 3 seconds
  //some function to buzz the buzzer

  //some code to make red light be for 17 sec

  
}

void RedFlashing(){
  digitalWrite(RED,HIGH);
  //wait
  digitalWrite(RED,LOW);
  //wait
  return;
}

void GLA(){
  digitalWrite(GREEN_LEFT_ARROW, HIGH);
  //wait
  digitalWrite(GREEN_LEFT_ARROW, LOW);
  //wait
}
