#include "main.h"
#include "config.h"
using namespace okapi;
void initialize() {
  front_intake.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);
  back_intake.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);
  lift.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);
  front_intake.tarePosition();
  back_intake.tarePosition();
  liftR.tarePosition();
  liftL.tarePosition();
  //auton_selector();
}

void autonomous() {
  printf("%d\n", lift.getPosition());
  /*
  joystick.clear();
  delay(100);
  joystick.setText(0, 0, i + "");
  delay(100);
  switch(i){
    case 0: mbl_goal();
    break;
    case 1: left_win_point();
    break;
    case 2: right_win_point();
    break;
  }
  stop();
  */
}

void opcontrol() {
  while(true){
    chassis->getModel()->arcade(
      joystick.getAnalog(ControllerAnalog::leftY),
      joystick.getAnalog(ControllerAnalog::rightX)
    );

    if ( frontTakeIn.isPressed() ) {

      front_clamp ();

    } else if ( frontTakeOut.isPressed() ) {

      front_unclamp ();

    } else {

      front_intake.moveVoltage(0);

    }

    if ( backTakeIn.isPressed() ) {

      back_clamp ();

    } else if (backTakeOut.isPressed()) {

      back_unclamp ();

    } else {

      back_intake.moveVoltage(0);

    }

    if ( liftUp.isPressed() ) {

      lift_up ();

    } else if ( liftDown.isPressed() ) {

      lift_down ();

    } else {

      lift.moveVelocity(0);

    }

    delay(20);
  }
}
