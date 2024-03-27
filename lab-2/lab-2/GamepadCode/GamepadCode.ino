/*
  Serial-WR

  Output hello to Serial
  Read input from Serial. If there is a 'E' detected, flip the LED

  yluo
  
*/
#define SW_pin 2
#define X_pin_Joystick A2
#define Y_pin_Joystick A1
#define X_max 1024
#define X_min 0
#define Y_min 0
#define Y_max 1024
#define tolerance 50
#define buzzer_pin 12

const int X_mid_left = ((X_max-X_min)/2) - tolerance;
const int X_mid_right = ((X_max-X_min)/2) + tolerance;
const int Y_mid_up = ((Y_max-Y_min)/2) + tolerance;
const int Y_mid_down =((Y_max-Y_min)/2) - tolerance; 

// LED status
int led_status = HIGH;
int incomingByte = 0;

// the setup routine runs once when you press reset:
void setup() {
  pinMode(SW_pin, INPUT);
  digitalWrite(SW_pin, HIGH);
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  pinMode(buzzer_pin, OUTPUT);   // turn the LED on (HIGH is the voltage level)
  led_status = HIGH;
}

// the loop routine runs over and over again forever:
void loop() {
  // read from the Serial port:
  if (Serial.available() == 0) {
    //X outputs
    if (analogRead(X_pin_Joystick) < X_mid_left) { 
      Serial.println("A"); // left
    }
    if (analogRead(X_pin_Joystick) > X_mid_right) { 
      Serial.println("D"); // right
    }

    //Y outputs
    if (analogRead(Y_pin_Joystick) < Y_mid_down) { 
      Serial.println("W"); // down
    }
    if (analogRead(Y_pin_Joystick) > Y_mid_up) { 
      Serial.println("S"); // up
    }
  }
  if(Serial.read() == 'E' && Serial.available() == 0) {
    digitalWrite(buzzer_pin, HIGH);
    delay(35);
  }
  else{
    digitalWrite(buzzer_pin, LOW);
  }
    delay(50);
}
