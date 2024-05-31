// planner.ino
//
// May 1, 2024
// Peter F. Klemperer
//
// The purpose of this file is to facilitate long
// term planning for the egg robots target angles.
// Currently, a series of target angles are defined
// in the array TARGET_ANGLE_STATES. Each state is
// held for TIME_IN_STATE_SEC.
//
// A damping factor DAMP_DEG_PER_SEC is applied to 
// smooth out the transitions between the target angles.
//

// Configure the goals for the planner
// how long in each state
// number of states
// array of target angles in degrees with 0 as down
const int TIME_IN_STATE_SEC = 30;
const int NUM_STATES = 2;
const float TARGET_ANGLE_STATES[2] = {35.0, -35.0};

// Configure damping factor
const float DAMP_DEG_PER_SEC = 5;

int _planner_state(float time_s) {
  return ((int) time_s / TIME_IN_STATE_SEC) % NUM_STATES;
}

float _get_goal_angle(int current_state) {
  return TARGET_ANGLE_STATES[current_state];
}

float _target_angle_damper(float goal_angle) {
  static bool first_run = true;
  static float previous_target_angle;
  static float previous_time_s;

  float current_time_s = millis() / 1000.0;

  if( first_run ) {
    previous_time_s = millis() / 1000.0;
    first_run = false;
  }

  float time_elapsed_s = current_time_s - previous_time_s;

  float damping = DAMP_DEG_PER_SEC * time_elapsed_s;
  float target_angle_difference = (goal_angle - previous_target_angle);
  float constrained_difference = constrain(target_angle_difference, -damping, damping);
  float target_angle = previous_target_angle + constrained_difference;

  // Serial.print("goal_angle\t");
  // Serial.print(goal_angle);
  // Serial.print("\tprevious_target_angle\t");
  // Serial.print(previous_target_angle);
  // Serial.print("\tdamping\t");
  // Serial.print(damping);
  // Serial.print("\ttarget_angle_difference\t");
  // Serial.print(target_angle_difference);
  // Serial.print("\tconstrained_difference\t");
  // Serial.print(constrained_difference);
  // Serial.print("\ttarget_angle\t");
  // Serial.println(target_angle);
  
  previous_target_angle = target_angle;
  previous_time_s = current_time_s;

  return target_angle;
}

float planner() {
  static bool first_run = true;
  static float start_time_s;

  if( first_run ) {
    start_time_s = millis() / 1000.0;
    first_run = false;
  }

  float elapsed_time_s = millis() / 1000.0 - start_time_s;

  int state_counter = _planner_state(elapsed_time_s);
  float goal_angle = _get_goal_angle(state_counter);
  float target_angle = _target_angle_damper(goal_angle);

  // Serial.print("elapsed_time_s:\t");
  // Serial.print(elapsed_time_s);
  // Serial.print("\tstate_counter:\t");
  // Serial.print(state_counter);
  // Serial.print("\tgoal_angle:\t");
  // Serial.print(goal_angle);
  // Serial.print("\ttarget_angle:\t");
  // Serial.println(target_angle);

  return target_angle;
}