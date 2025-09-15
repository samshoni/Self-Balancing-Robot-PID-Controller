#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;

// Motor pins
const int ENA = 5;
const int IN1 = 7;
const int IN2 = 8;
const int ENB = 6;
const int IN3 = 9;
const int IN4 = 10;

long timer = 0;
float pitch = 0;
float motorOutput = 0;  // smoothed motor speed

// PD gains
float Kp = 90;       // proportional gain
float Kd = 30;       // derivative gain
float setPoint = -3.8; // upright pitch

// Roll threshold
float rollLimit = 15; // degrees

void setup() {
  Serial.begin(115200);
  Wire.begin();

  // Initialize MPU6050
  mpu.initialize();
  if (!mpu.testConnection()) {
    Serial.println("MPU6050 connection failed!");
    while (1);
  }
  Serial.println("MPU6050 connected!");

  // Motor setup
  pinMode(ENA, OUTPUT); pinMode(IN1, OUTPUT); pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT); pinMode(IN3, OUTPUT); pinMode(IN4, OUTPUT);

  stopMotors();
  timer = millis();
}

void loop() {
  int16_t ax, ay, az, gx, gy, gz;
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  // Convert raw data
  float accelX = ax / 16384.0;
  float accelY = ay / 16384.0;
  float accelZ = az / 16384.0;
  float gyroX = gx / 131.0; // deg/sec

  // Compute pitch and roll from accel
  float accelPitch = atan2(accelY, accelZ) * 180 / PI;
  float roll = atan2(-accelX, accelZ) * 180 / PI;

  // Stop motors if roll exceeds limit
  if (abs(roll) > rollLimit) {
    stopMotors();
    Serial.println("Sideways tilt! Motors stopped.");
    return;
  }

  // Delta time
  float dt = (millis() - timer) / 1000.0;
  timer = millis();

  // Complementary filter for pitch
  pitch = 0.98 * (pitch + gyroX * dt) + 0.02 * accelPitch;

  // PD control
  float error = pitch - setPoint;
  float derivative = gyroX;
  float targetMotor = Kp * error + Kd * derivative;

  // Limit motor output
  targetMotor = constrain(targetMotor, -200, 200);

  // Smooth motor output
  motorOutput = 0.7 * motorOutput + 0.3 * targetMotor;

  // Motor control
  if (motorOutput > 0) moveBackward(motorOutput);
  else if (motorOutput < 0) moveForward(-motorOutput);
  else stopMotors();

  // Debug
  Serial.print("Pitch: "); Serial.print(pitch);
  Serial.print(" | Roll: "); Serial.print(roll);
  Serial.print(" | Motor: "); Serial.println(motorOutput);

  delay(10); // loop fast
}

// --- Motor functions ---
void moveForward(int pwm) {
  digitalWrite(IN1,HIGH); digitalWrite(IN2,LOW); analogWrite(ENA,pwm);
  digitalWrite(IN3,HIGH); digitalWrite(IN4,LOW); analogWrite(ENB,pwm);
}

void moveBackward(int pwm) {
  digitalWrite(IN1,LOW); digitalWrite(IN2,HIGH); analogWrite(ENA,pwm);
  digitalWrite(IN3,LOW); digitalWrite(IN4,HIGH); analogWrite(ENB,pwm);
}

void stopMotors() {
  analogWrite(ENA,0); analogWrite(ENB,0);
  digitalWrite(IN1,LOW); digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW); digitalWrite(IN4,LOW);
}
