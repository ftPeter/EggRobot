float pidControl(float input, float target) {
  /* PID AND MOTOR CONSTANTS */
  const float Kp = 1.0;
  const float Ki = 0.5;
  const float Kd = 0.1;

  /* STATIC VARIABLES */
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

  float output  = (Kp * error  + Ki * integral  + Kd * derivative);

  // update previous values
  prev_time_ms = current_time_ms;
  prev_error  = error;

  return output;
}