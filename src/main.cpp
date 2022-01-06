#include "main.h"
#include "config.h"
#include "math.h"
using namespace okapi;
void initialize() {
  front_intake.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);
  back_intake.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);
  lift.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);
  front_intake.tarePosition();
  back_intake.tarePosition();
  liftR.tarePosition();
  liftL.tarePosition();
  imu_x.reset();
  imu_z.reset();
  Task acceleration_tracker(acceleration_tracker,"Acceleration Tracker");
  //auton_selector();
}
void acceleration_tracker(){
    int time = 5
    acceleration.push_back(0.0)
    while(auton_state==false){
        while(auton_state==true){
            double prev_vel = acceleration.at(ind-1);
            double z_accel = imu_z.getAcceleration();
            double x_accel = imu_x.getAcceleration();
            double accel = sqrt((z_accel*z_accel)+(x_accel*x_accel));
            acceleration.push_back(prev_vel+(accel*time));
            totalTime = totalTime + time;
            ind = ind+1;
            delay(time);
        }
        delay(time);
    }
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
