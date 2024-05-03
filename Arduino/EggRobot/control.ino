/* PID AND MOTOR CONSTANTS */
const float KP = 0.5;
const float KI = 0.2;
const float KD = 0.01;

float pidControl(float input, float target) {
  // necessary to support soft-start
  float Kp = KP;
  float Ki = KI;
  float Kd = KD;

  /* STATIC VARIABLES */
  static bool first_run = true;
  static unsigned long prev_time_ms;
  static float prev_error;
  static float integral;

  /* TIME DURATION SINCE LAST UPDATE */
  unsigned long current_time_ms = millis();
  long duration_ms = current_time_ms - prev_time_ms;
  float duration_s = float(duration_ms)/1000.0;

  /* CALCULATE ERROR : error = target - measured */
  float error  = target - input;
 
  /* PID CALCULATIONS*/
  integral  +=  (error * duration_s);
  float derivative  = (error - prev_error) / duration_s;

  /* SOFTEN-START */
  const float soft_start_s = 2000.0;
  if( current_time_ms < soft_start_s ) {
    Serial.print("current_time_ms\t");
    Serial.println(current_time_ms);
    Kp = Kp * current_time_ms / soft_start_s ;
    Ki = 0;
    Kd = 0;
    integral = 0;
  }

  float output  = (Kp * error  + Ki * integral  + Kd * derivative);

  // update previous values
  prev_time_ms = current_time_ms;
  prev_error  = error;

  return output;
}