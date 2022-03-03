#include "config.h"
using namespace okapi;

void drive_funct (void*) {

  while(true){

    chassis->getModel()->arcade(

      joystick.getAnalog(okapi::ControllerAnalog::leftY),

      joystick.getAnalog(okapi::ControllerAnalog::rightX)

    );

    delay(20);

  }

  delay(20);

}

void acceleration_tracker (void*) {

    int time = 50;
    acceleration.push_back(0.0);

    while (true && auton_state) {

        double prev_vel = acceleration.at(ind - 1);

        double y_accel = imu_y.getAcceleration();
        double x_accel = imu_x.getAcceleration();

        double accel = sqrt ((x_accel * x_accel) + (y_accel * y_accel));

        acceleration.push_back( prev_vel + (accel * time) );
        totalTime += time;

        ind += 1;
        delay(time);

    }

}
