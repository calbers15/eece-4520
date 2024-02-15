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

  

  while(digitalRead(Button) == LOW)
  {
    RedFlashing();
  }
}

void loop() {
  
  // put your main code here, to run repeatedly:

  //some code to make red light flash 1-1 for 3 sec
  GLAFlashing();
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

ISR(TIMER1_COMPA_vect){//timer1 interrupt 1Hz toggles pin 13 (LED)
//generates pulse wave of frequency 1Hz/2 = 0.5kHz (takes two cycles for full wave- toggle high then toggle low)
  if (toggle1){
    digitalWrite(13,HIGH);
    toggle1 = 0;
  }
  else{
    digitalWrite(13,LOW);
    toggle1 = 1;
  }
}

void RedFlashing(){
  digitalWrite(RED,HIGH);
  //wait
  digitalWrite(RED,LOW);
  //wait
  return;
}

void GLAFlashing(){
  digitalWrite(GREEN_LEFT_ARROW, HIGH);
  //wait
  digitalWrite(GREEN_LEFT_ARROW, LOW);
  //wait
}
