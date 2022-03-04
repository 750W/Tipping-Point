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

void inertial_tracker (void*) {

    rotation_values.push_back(0.0);

    while (true && auton_state) {

        rotation_values.push_back(imu.get_rotation());
        ind += 1;
        delay(50);

    }

}
