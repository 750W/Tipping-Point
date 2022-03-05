#include "config.h"
using namespace okapi;

void drive_PID (int ticks) {

  double kP = 0.6;
  double kD = 0.0;

  double desired_value = ticks;
  double sensor_value = shaft_encoder.get();
  double error = desired_value - (fabs(sensor_value));

  double derivative, previous_error, velocity;
  previous_error = 0.0;
  derivative = 0.0;
  velocity = 200;


  while((int)error > 0) {

    sensor_value = shaft_encoder.get();
    error = desired_value - (fabs(sensor_value));
    printf("sensor: %f ", (fabs(sensor_value)));
    printf("error: %f ", error);
    derivative += previous_error;
    velocity = (kP * error + kD * derivative);

    if(velocity >= 200) {
      velocity = 200;
    } else if(velocity < 80) {
      break;
    }

    printf("velocity: %f ", velocity);

    move_dist(velocity, 20);

    previous_error = error;

  }

}
