#include "config.h"
using namespace okapi;

void drive_PID (double dist) {

  double desired_val = dist;
  double error = desired_val - getCurrentPosition();
  double kP = 0.155;
  double kD = 0.0;

  double velocity = 200;
  double prev_error = 0.0;
  double derivative = error - prev_error;

  while((int)error > 0) {

    error = desired_val - getCurrentPosition();
    derivative = error - prev_error;
    velocity = error * kP + derivative * kD;

    if(velocity > 200) {

      velocity = 200;

    } else if(velocity < 15) {

      break;
      
    }

    move_dist(velocity, 25);
    prev_error = error;

  }

  move_dist(0, 25);

}
