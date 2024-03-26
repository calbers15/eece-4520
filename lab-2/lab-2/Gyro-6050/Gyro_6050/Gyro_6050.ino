#include <Wire.h>

#define buzzer_pin 12
const int MPU_addr = 0x68;  // I2C address of the MPU-6050
int16_t GyX, GyY, GyZ;
int snakeX = 0; // Initial position of the snake
int snakeY = 0;
int directionX = 1; // Initial direction of the snake
int directionY = 0;
unsigned long lastMoveTime = 0; // To control snake movement speed

void setup() {
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);      // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  Serial.begin(9600);
  pinMode(buzzer_pin, OUTPUT);
}

void loop() {
  
  // Adjust snake movement speed here
    //lastMoveTime = currentTime;
    readGyro();
    updateDirection();
    //moveSnake();
    delay(250);
  if(Serial.read() == 'E' && Serial.available() == 0) {
    // flip LED
    digitalWrite(buzzer_pin, HIGH);
    delay(35);
  }
  else{
    digitalWrite(buzzer_pin, LOW);
  }
    delay(50);
  
}

void readGyro() {
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x43);  // starting with register 0x43 (GYRO_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr, 6, true);  // request a total of 6 registers
  GyX = Wire.read() << 8 | Wire.read();  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY = Wire.read() << 8 | Wire.read();  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyZ = Wire.read() << 8 | Wire.read();  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
}

void updateDirection() {
  // Threshold for considering movement
  const int movementThreshold_x = 12500;
  const int movementThreshold_y = 10500;

  // Check if there is significant movement
  if (abs(GyX) > movementThreshold_x || abs(GyY) > movementThreshold_y) {
    if (abs(GyX) > abs(GyY)) {
      // If X-axis rotation is greater, change Y direction
      if (GyX > 0) {
        directionY = -1;
        Serial.println("S"); // Up
      } 
      else {
        directionY = 1;
        Serial.println("W"); // Down
      }
      directionX = 0;
    } 
    
    else if (abs(GyX) < abs(GyY)) {
      // If Y-axis rotation is greater, change X direction
      if (GyY > 0) {
        directionX = -1;
        Serial.println("D"); // Left
      } 
      else {
        directionX = 1;
        Serial.println("A"); // Right
      }
      directionY = 0;
    }
  }
  else{
    directionX = 0;
    directionY = 0;
    Serial.println("");
  }
  
}


void moveSnake() {
  
  //Debug print statements
  /*Serial.print("Snake Moving X = ");
  //Serial.print(GyX);
  Serial.print(directionX);
  Serial.print(", Y = ");
  //Serial.println(GyY);
  Serial.println(directionY);*/

  /*if(directionY == -1){
    Serial.println("S");
  }
  else if(directionY == 1){
    Serial.println("W");
  }
  else if(directionX == -1){
    Serial.println("D");
  }
  else if(directionX == 1){
    Serial.println("A");
  }
  else{
    Serial.println("");
  }*/

}