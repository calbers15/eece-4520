//#include "TimerSample.ino"
#define GREEN 53 //assigning pins specific values without using globals
#define YELLOW 52
#define RED 51
#define GLA 50
#define BUZZER 2 // change to a pin labeled as analog or pwm
#define Button 49

char toggle1;

void setup() {
  // put your setup code here, to run once:

  
  pinMode(GREEN, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  pinMode(RED, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(Button, INPUT);
  pinMode(GLA, OUTPUT);

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

  

  while(digitalRead(Button) == HIGH)
  {
    digitalWrite(RED, HIGH);
    delay(1000);
    if(digitalRead(Button)==LOW){break;}
    digitalWrite(RED, LOW);
    delay(1000);
  }
}


unsigned long previousMillis = 0;
unsigned long interval = 1000;
void loop() {
  

  unsigned long currentMillis = millis();
  // put your main code here, to run repeatedly:

  //some for loop for GLA to be solid for 3 seconds
  //some for loop for flahsing GLA for 3 seconds (on 1 sec-off 1 sec(aka 1-1))
  //some function to buzz the buzzer
  controlSignal(GLA, 3000);
  
  //some code to make green light stay solid for 9 seconds
  controlSignal(GREEN, 12000);
  //some code to make green light flash 1-1 for 3 seconds
  //some function to buzz the buzzer
  controlSignal(YELLOW, 15000);
  //some code to make yellow light solid for 3 seconds
  //some function to buzz the buzzer
  controlSignal(RED, 32000);
  
  //some code to make red light be for 17 sec
  
  //some code to make red light flash 1-1 for 3 sec
  //some function to buzz the buzzer
  

    
}

ISR(TIMER1_COMPA_vect){//timer1 interrupt 1Hz toggles pin 13 (LED)
//generates pulse wave of frequency 1Hz/2 = 0.5kHz (takes two cycles for full wave- toggle high then toggle low) 
    
  if (toggle1){
    toggle1 = 0;
  }
  else{
    toggle1 = 1;
  }
}


void controlSignal(int pin, unsigned long duration){
  digitalWrite(pin, HIGH);
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= duration){
    previousMillis = currentMillis;
    FlashingSignal(pin);
  }
}

void FlashingSignal(int pin){
  analogWrite(BUZZER, 256/4);
  digitalWrite(pin, LOW);
  delay(1000);
  digitalWrite(pin, HIGH);
  delay(1000);
  digitalWrite(pin, LOW);
  delay(1000);
  analogWrite(BUZZER, 0);
}
