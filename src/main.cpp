#include "config.h"
using namespace okapi;

void initialize() {

  piston.set_value(false);

  front_intake.setBrakeMode(AbstractMotor::brakeMode::hold);
  back_intake.setBrakeMode(AbstractMotor::brakeMode::hold);
  ring_intake.setBrakeMode(AbstractMotor::brakeMode::hold);
  lift.setBrakeMode(AbstractMotor::brakeMode::hold);

  front_intake.tarePosition();
  back_intake.tarePosition();
  lift.tarePosition();
  ring_intake.tarePosition();

  imu_x.reset();
  imu_z.reset();

  contract_piston(0);

  Task tracker_task(acceleration_tracker,(void*)"not needed","tracker task");
  auton_selector();
}

void autonomous() {

  auton_state = true;

  switch (i) {

    case 0: mbl_goal();
    break;

    case 1: left_win_point();
    break;

    case 2: right_win_point();
    break;

  }

  mbl_goal();
  drive_PID(1000.0);

  auton_state = false;

}

void opcontrol() {

  Task drive(drive_funct, (void*)"not needed", "driver control task");
  while(true) {

    if ( l1.isPressed() ) {

      front_clamp();

    } else if ( r1.isPressed() ) {

      front_unclamp();

    } else {

      front_intake.moveVelocity(0);

    }

    if ( l2.isPressed() ) {

      back_clamp();

    } else if ( r2.isPressed() ) {

      back_unclamp();

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
