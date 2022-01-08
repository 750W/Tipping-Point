#include "config.h"
using namespace okapi;

void initialize() {
  front_intake.setBrakeMode(AbstractMotor::brakeMode::hold);
  back_intake.setBrakeMode(AbstractMotor::brakeMode::hold);
  lift.setBrakeMode(AbstractMotor::brakeMode::hold);
  front_intake.tarePosition();
  back_intake.tarePosition();
  liftR.tarePosition();
  liftL.tarePosition();
  imu_x.reset();
  imu_z.reset();
  //fix this !!!!!!
    Task tracker_task(acceleration_tracker,(void*)"not needed",TASK_PRIORITY_DEFAULT,TASK_STACK_DEPTH_DEFAULT,"tracker task");
  //auton_selector();
}

void autonomous() {
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

    if ( up.isPressed() ) {

      lift_up ();

    } else if ( down.isPressed() ) {

      lift_down ();

    } else if ( left.isPressed() ) {

      lift_PID(900);

    } else if ( right.isPressed() ) {

      lift_PID(-900);

    } else {

      lift.moveVelocity(0);

    }

    delay(20);
  }
}
