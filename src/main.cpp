#include "config.h"
using namespace okapi;

void initialize() {

  piston.set_value(false);

  back_intake.setBrakeMode(AbstractMotor::brakeMode::hold);
  ring_intake.setBrakeMode(AbstractMotor::brakeMode::hold);
  lift.setBrakeMode(AbstractMotor::brakeMode::hold);

  back_intake.tarePosition();
  liftL.tarePosition();
  liftR.tarePosition();
  ring_intake.tarePosition();

  imu.reset();
  shaft_encoder.reset();

  contract_piston(0);

  //auton_selector();
}

void autonomous() {

  /*

  switch (i) {

    case 0: mbl_goal();
    break;

    case 1: left_win_point();
    break;

    case 2: right_win_point();
    break;

  }

  */

}

void opcontrol() {

  Task drive(drive_funct, (void*)"not needed", "driver control task");
  while(true) {

    if ( l1.isPressed() ) {

      front_clamp();

    } else if ( r1.isPressed() ) {

      front_unclamp();

    }

    if ( l2.isPressed() ) {

      back_up();

    } else if ( r2.isPressed() ) {

      back_down();

    } else {

      back_intake.moveVoltage(0);

    }

    if ( x.isPressed() ) {

      ring_forward();

    } else if ( b.isPressed() ) {

      ring_reverse();

    } else if ( a.isPressed() ) {

      ring_stop();

    } else {

      back_intake.moveVoltage(0);

    }

    if ( up.isPressed() ) {

      lift_up();

    } else if ( down.isPressed() ) {

      lift_down();

    }  else {

      lift.moveVelocity(0);

    }

    delay(20);

  }

}
