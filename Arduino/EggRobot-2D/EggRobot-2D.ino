/* EggRobot Version 4.0
 *
 * by Peter F. Klemperer
 * May 29, 2024
 */

#include <Servo.h>

Servo pendulumServo;
Servo leftLegServo; 
Servo rightLegServo;

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
  initializeIMU();
  delay(100); // give the IMU time before the servo turns on, power spike from servo or something...

  // attach the servo
  pendulumServo.attach(0);
  delay(20);
  leftLegServo.attach(1);
  delay(20);
  rightLegServo.attach(2);
  delay(100);

  // Initialize serial for debugging communication
  Serial.begin(9600);
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
  // servoTest();

  //step();

  serial_control_loop();

  // // consult the planner for the target lean angle
  // float targetAngle = planner(); //0

  // // average several IMU readings
  // // before updating the servo
  // int filter = 0;
  // for(int c = 0; c < 10; c++) {
  //   filter += getRotationPose();
  //   delay(5);
  // }
  // int scaledRotation = filter / 10;
  
  // // calculate the target pendulum angle
  // float bodyAngle = pidControl( scaledRotation, targetAngle);

  // Serial.print("scaledRotation ");
  // Serial.print(scaledRotation);
  // Serial.print("\ttargetAngle ");
  // Serial.print(targetAngle);
  // Serial.print("\tbodyAngle ");
  // Serial.print(bodyAngle);
  

  // // command the pendulum
  // float pendulumAngle = translateAngle(bodyAngle);
  // Serial.print("\tpendulumAngle ");
  // Serial.print(pendulumAngle);
  // Serial.print("\t");
  // positionPendulum(pendulumAngle);

  // // delay(100);
}
