#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

Adafruit_MPU6050 mpu;

int ledPin = 8;

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);

  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) { delay(10); }
  }
  Serial.println("MPU6050 Found!");

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
}

void loop() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  // Tilt detection using X-axis acceleration
  if (a.acceleration.x > 5) {  // Forward tilt
    digitalWrite(ledPin, HIGH);
    Serial.println("LED ON - Tilt Forward");
  } else if (a.acceleration.x < -5) { // Backward tilt
    digitalWrite(ledPin, LOW);
    Serial.println("LED OFF - Tilt Backward");
  }

  delay(200);
}
