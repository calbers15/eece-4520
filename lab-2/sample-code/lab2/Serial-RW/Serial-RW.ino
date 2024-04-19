/*
  Serial-WR

  Output hello to Serial
  Read input from Serial. If there is a 'E' detected, flip the LED

  yluo
  
*/
#define buzzer_pin 12
// LED status
int led_status = HIGH;
int incomingByte = 0;

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(buzzer_pin, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  led_status = HIGH;
}

// the loop routine runs over and over again forever:
void loop() {
  // read from the Serial port:
  if (Serial.available() > 0) {
    // read the incoming byte:
    incomingByte = Serial.read();
    Serial.println(incomingByte);
    
    if(incomingByte == 'E') {
      // flip LED
      led_status = (led_status == HIGH)? LOW : HIGH;
      digitalWrite(LED_BUILTIN, led_status);
      digitalWrite(buzzer_pin, HIGH);
      delay(100);
      digitalWrite(buzzer_pin, LOW);
    }
  }

  delay(1000);
  Serial.println("Hello");

}
