// output.ino
//
// Contains the parameters and functions for calculating
// the 1D Egg Bot pendulum angle
//
// May 17, 2024
// Peter F. Klemperer

// CONSTANTS
const float L_MM = 8.382;
const float R_MM = 47.00;
const float CORRECTIONFACTOR = acos(L_MM/R_MM) * 57.2958; // 79.726890811277149

// translateAngle
// input is the requested angle of the body
// output is the required pendulum angle
float translateAngle(float bodyAngle) {
  // Serial.print("\nXXXXX\n");
  // Serial.print("bodyAngle ");
  // Serial.print(bodyAngle);
  // Serial.print("\t");
  // Serial.print(bodyAngle*0.0174533);
  // Serial.print("\t");
  // Serial.print(sin(bodyAngle*0.0174533));
  // Serial.println("\nXXXXXX");
  return sin(bodyAngle*0.0174533) * CORRECTIONFACTOR;
}