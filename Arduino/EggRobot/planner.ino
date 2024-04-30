float planner() {
  static bool first_run = true;
  static float start_time_s;

  if( first_run ) {
    start_time_s = millis() / 1000.0;
    first_run = false;
  }

  float elapsed_time_s = millis() / 1000.0 - start_time_s;

  float goal_angle = 10;

  // Serial.print("planner: ");
  // Serial.print(goal_angle);
  // Serial.print("\t");
  // Serial.println(elapsed_time_s);

  return goal_angle;
}