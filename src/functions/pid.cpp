#include "config.h"
using namespace okapi;

void drive_PID (double dist) {

  double kP = 0.3;
  double kD = 0.0;

  double desired_value = dist * 360.0 / (2 * M_PI * 0.02);
  double sensor_value = (shaft_encoder.controllerGet() * 360.0) / 1800.0;
  double error = desired_value - sensor_value;

  double derivative, previous_error, velocity;
  previous_error = 0.0;
  derivative = 0.0;
  velocity = 100;


  while((int)error > 0) {

    sensor_value = (shaft_encoder.controllerGet() * 360.0) / 1800.0;
    error = desired_value - sensor_value;
    printf("sensor:%f ", sensor_value);
    printf("\nerror:%f ", error);
    derivative += previous_error;
    velocity = kP * error + kD * derivative;

    if(velocity > 100) {
      velocity = 100;
    }

    printf("velocity%f", velocity);

    move_dist(velocity, 20);

    previous_error = error;

  }

}
