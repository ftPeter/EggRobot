

#include <Servo.h>

Servo pendulumServo; 

int pos = 90;    // variable to store the servo position

#include <Wire.h>
#include <LSM6.h>
#include <LIS3MDL.h>

LSM6 imu;
LIS3MDL mag;

char report[160];

void setup() {
  pendulumServo.attach(0);

    Serial.begin(9600);
  Wire.begin();

  if (!imu.init())
  {
    Serial.println("Failed to detect and initialize IMU!");
    //while (1);
  }
  imu.enableDefault();

  if (!mag.init())
  {
    Serial.println("Failed to detect and initialize magnetometer!");
    //while (1);
  }
  mag.enableDefault();
}

// provide a position -128 to 127 inclusive
// and then the servo is positioned within 
// it's allowed range
void positionServo(int position) {
  int MIN = 65;
  int MAX = 125;

  int scaledP = map(position, -180, 180, 180, 0);
  scaledP = constrain(scaledP, MIN, MAX);

  Serial.println(scaledP);

  // what is the range of pendulumServo? 0-180
  pendulumServo.write(scaledP);
}

int getRotationPose() {
  imu.read();
  mag.read();

  // snprintf(report, sizeof(report), "P: %3d A: %6d %6d %6d    G: %6d %6d %6d  M: %6d %6d %6d",
  //   pos,
  //   imu.a.x, imu.a.y, imu.a.z,
  //   imu.g.x, imu.g.y, imu.g.z,
  //   mag.m.x, mag.m.y, mag.m.z);
  // Serial.println(report);

  return 90 * imu.a.x / 16000;
}

void loop() {




  int scaledRotation = getRotationPose();
  float targetAngle = pidControl( scaledRotation, 0.0);

  Serial.print(scaledRotation);
  Serial.print("\t");
  Serial.print(targetAngle);
  Serial.print("\t");

  positionServo(targetAngle);

  delay(100);
}
