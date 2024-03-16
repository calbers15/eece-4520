#include <Wire.h>

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
}

void loop() {
  unsigned long currentTime = millis();
  if (currentTime - lastMoveTime >= 100) { // Adjust snake movement speed here
    lastMoveTime = currentTime;
    readGyro();
    updateDirection();
    moveSnake();
  }
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
  // Adjust direction based on gyro readings
  if (abs(GyX) > abs(GyY)) {
    // If X-axis rotation is greater, change Y direction
    if (GyX > 0) {
      directionY = -1; // Up
    } else {
      directionY = 1; // Down
    }
    directionX = 0;
  } else {
    // If Y-axis rotation is greater, change X direction
    if (GyY > 0) {
      directionX = -1; // Left
    } else {
      directionX = 1; // Right
    }
    directionY = 0;
  }
}

void moveSnake() {
  // Update snake position based on direction
  snakeX += directionX;
  snakeY += directionY;
  // Add game logic for collision detection, updating display, etc.
  // This is a simplified example.
  Serial.print("Snake Position: X = ");
  Serial.print(snakeX);
  Serial.print(", Y = ");
  Serial.println(snakeY);
}