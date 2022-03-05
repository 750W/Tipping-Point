#include "config.h"

void move_dist (double spd, int time) {

  drive_fL.moveVelocity(spd);
  drive_fR.moveVelocity(spd);
  drive_bL.moveVelocity(spd);
  drive_bR.moveVelocity(spd);

  delay(time);

}

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
