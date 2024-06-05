void servoTest() {
    // rightLegServo.write(89);
  // leftLegServo.write(120);
  //pendulumServo.write(84);

  // positionLeftLeg(+50.0);
  positionRightLeg(+30.0);
  // positionPendulum(+30.0);
  delay(10);
}

// positionServo 
// takes a position target for
// pendulum in degrees from 0 (down)
// and then the servo is positioned within 
// it's allowed range
void positionPendulum(float position) {
  const int MIDDLE = 83;
  const int RANGE = 30;
  const int MIN = MIDDLE - RANGE;
  const int MAX = MIDDLE + RANGE;
  const int MIDDLE_OFFSET = MIDDLE - 90;

  int scaledP = map(position, -180, 180, 180, 0);
  scaledP += MIDDLE_OFFSET;
  scaledP = constrain(scaledP, MIN, MAX);

  // what is the range of pendulumServo? 0-180
  pendulumServo.write(scaledP);
  Serial.print("positionPendulum ");
  Serial.println(scaledP);
}

// positionServo 
// takes a position target for
// pendulum in degrees from 0 (down)
// and then the servo is positioned within 
// it's allowed range
void positionLeftLeg(float position) {
  const int MIDDLE = 89;
  const int RANGE = 30;
  const int MIN = MIDDLE - RANGE;
  const int MAX = MIDDLE + RANGE;
  const int MIDDLE_OFFSET = MIDDLE - 90;

  int scaledP = map(position, -180, 180, 180, 0);
  scaledP += MIDDLE_OFFSET;
  scaledP = constrain(scaledP, MIN, MAX);

  // what is the range of pendulumServo? 0-180
  leftLegServo.write(scaledP);
  Serial.print("positionLeftLeg ");
  Serial.println(scaledP);
}

// positionServo 
// takes a position target for
// pendulum in degrees from 0 (down)
// and then the servo is positioned within 
// it's allowed range
void positionRightLeg(float position) {
  const int MIDDLE = 92;
  const int RANGE = 30;
  const int MIN = MIDDLE - RANGE;
  const int MAX = MIDDLE + RANGE;
  const int MIDDLE_OFFSET = MIDDLE - 90;

  int scaledP = map(position, -180, 180, 180, 0);
  scaledP += MIDDLE_OFFSET;
  scaledP = constrain(scaledP, MIN, MAX);

  // what is the range of pendulumServo? 0-180
  rightLegServo.write(scaledP);
  Serial.print("positionRightLeg ");
  Serial.println(scaledP);
}