/* EggRobot Version 1.5
 *
 * by Peter F. Klemperer
 * April 30, 2024
 */

#include <Servo.h>

Servo pendulumServo; 

#include <Wire.h>
#include <LSM6.h>
#include <LIS3MDL.h>

LSM6 imu;
LIS3MDL mag;

char report[160];

void initializeIMU() {
  // Initialize the IMU and Magnetometer
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

void setup() {
  animate_setup();

  initializeIMU();
  delay(100); // give the IMU time before the servo turns on, power spike from servo or something...

  // attach the servo
  pendulumServo.attach(0);
  delay(100);

  // Initialize serial for debugging communication
  Serial.begin(9600);
}

// positionServo 
// takes a position target for
// pendulum in degrees from 0 (down)
// and then the servo is positioned within 
// it's allowed range
void positionServo(float position) {
  const int MIN = 65;
  const int MAX = 125;
  const int MIDDLE_OFFSET = 96 - 90;

  int scaledP = map(position, -180, 180, 180, 0);
  scaledP += MIDDLE_OFFSET;
  scaledP = constrain(scaledP, MIN, MAX);

  // what is the range of pendulumServo? 0-180
  pendulumServo.write(scaledP);
  Serial.print("positionServo ");
  Serial.println(scaledP);
}

// getRotationPose
// reads the imu and (roughly) returns the
// robot's lean angle (0 down)
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
  // consult the planner for the target lean angle
  float targetAngle = planner(); //0

  // average several IMU readings
  // before updating the servo
  int filter = 0;
  for(int c = 0; c < 10; c++) {
    filter += getRotationPose();
    delay(5);
  }
  int scaledRotation = filter / 10;
  
  // calculate the target pendulum angle
  float bodyAngle = pidControl( scaledRotation, targetAngle);

  Serial.print("scaledRotation ");
  Serial.print(scaledRotation);
  Serial.print("\ttargetAngle ");
  Serial.print(targetAngle);
  Serial.print("\tbodyAngle ");
  Serial.print(bodyAngle);
  

  // command the pendulum
  float pendulumAngle = translateAngle(bodyAngle);
  Serial.print("\tpendulumAngle ");
  Serial.print(pendulumAngle);
  Serial.print("\t");
  positionServo(pendulumAngle);

  // delay(100);
}
