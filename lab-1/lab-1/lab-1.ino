//#include "TimerSample.ino"
<<<<<<< Updated upstream
#define GREEN 55 //assigning pins specific values without using globals
#define YELLOW 54
#define RED 53
#define BUZZER 2
#define Button 52
#define GREEN_LEFT_ARROW 51
=======
#define GREEN 53 //assigning pins specific values without using globals
#define YELLOW 52
#define RED 51
#define GLA 50
#define BUZZER 2 // change to a pin labeled as analog or pwm
#define Button 3

int toggle1;
int loopTime;
>>>>>>> Stashed changes

void setup() {
  // put your setup code here, to run once:
  
  pinMode(GREEN, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  pinMode(RED, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(Button, INPUT);
<<<<<<< Updated upstream
  pinMode(GREEN_LEFT_ARROW, OUTPUT);

=======
  pinMode(GLA, OUTPUT);
  
>>>>>>> Stashed changes
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
  
  attachInterrupt(digitalPinToInterrupt(Button), initiateLoop, FALLING);//go to void loop() when button falling
  sei();//allow interrupts

  while(1)
  {
<<<<<<< Updated upstream
    RedFlashing();
=======
    if(toggle1 == 0){    digitalWrite(RED, HIGH);}
    if(toggle1 == 1){    digitalWrite(RED, LOW); }
>>>>>>> Stashed changes
  }
  initiateLoop();
}




void loop() {
  loopTime = 0;
  // put your main code here, to run repeatedly:

<<<<<<< Updated upstream
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

  
=======
  Lights(2, GLA);//5 seconds total
  
  Lights(5+9, GREEN);//12 seconds total
  
  digitalWrite(YELLOW, HIGH); //3 seconds total
  analogWrite(BUZZER, 256/4);
  do{}while(loopTime < 5+12+3);  
  digitalWrite(YELLOW, LOW);
  analogWrite(BUZZER,0);
    

  Lights(5+12+3+17,RED);//20 seconds total
>>>>>>> Stashed changes
}





ISR(TIMER1_COMPA_vect){//timer1 interrupt 1Hz toggles pin 13 (LED)
<<<<<<< Updated upstream
//generates pulse wave of frequency 1Hz/2 = 0.5kHz (takes two cycles for full wave- toggle high then toggle low)
=======
//generates pulse wave of frequency 1Hz/2 = 0.5kHz (takes two cycles for full wave- toggle high then toggle low) 
  loopTime++;
>>>>>>> Stashed changes
  if (toggle1){
    digitalWrite(13,HIGH);
    toggle1 = 0;
  }
  else{
    digitalWrite(13,LOW);
    toggle1 = 1;
  }
}

<<<<<<< Updated upstream
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
=======

void initiateLoop()
{
    detachInterrupt(digitalPinToInterrupt(Button));
}


void Lights(int solidTime, int pin)
{
  digitalWrite(pin, HIGH);
  do{}while(loopTime < solidTime);  
  analogWrite(BUZZER, 256/4); //some function to buzz the buzzer
  do
  {
    if(toggle1 == 1){digitalWrite(pin, LOW);}  //some code to make light flash 1-1 for 3 seconds
    if(toggle1 == 0){digitalWrite(pin, HIGH);}
  }while(loopTime < solidTime+3);
  analogWrite(BUZZER, 0);
  digitalWrite(pin, LOW);
>>>>>>> Stashed changes
}
