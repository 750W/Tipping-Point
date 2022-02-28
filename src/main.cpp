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

  //contract_piston(0);
  //Task tracker_task(acceleration_tracker,(void*)"not needed",TASK_PRIORITY_DEFAULT,TASK_STACK_DEPTH_DEFAULT,"tracker task");
  //auton_selector();
}

void autonomous() {

  auton_state = true;

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

  mbl_goal();
  //drive_PID({drive_fL, drive_bL}, {drive_fR, drive_bR}, 1000.0);

  auton_state = false;

  /*
  chassis -> setMaxVelocity (150);
  int count = 0;

  while ( !back_bumperswitch.isPressed()) {
    move_dist (-90, 25);
    count += 25;
  }
  stop();

  back_intake.moveVelocity(-400);
  delay(300);

  move_dist(150, 450);
  stop();

  chassis->turnToAngle(120_deg);
  back_unclamp();

  chassis->turnToAngle(-120_deg);

  move_dist(-150, 450);
  stop();

  chassis->turnToAngle(60_deg);
  move_dist(-150, 1400);
  stop();

  chassis->turnToAngle(-20_deg);
  move_dist(-150, 500);
  stop();

  front_intake.moveVoltage(8000);
  delay(200);

  stop();

  chassis->turnToAngle(90_deg);
  back_unclamp();
  stop();
  delay(20);

  move_dist(180, 20);
  chassis->turnToAngle(-45_deg);
  move_dist(180, 40);
  stop();

  chassis->turnToAngle(-90_deg);
  while ( !back_bumperswitch.isPressed()) {
    move_dist (150, 25);
    count += 25;
  }
  stop();

  front_clamp ();
  stop ();

  front_unclamp ();
  stop ();
*/
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

    /*else if ( back_bumperswitch.isPressed() ) {

      if ( b.isPressed() ) {

        back_auto_clamp();

      } else {

        back_auto_unclamp();

      }
      */

    if ( up.isPressed() ) {

      lift_up();

    } else if ( down.isPressed() ) {

      lift_down();

    }  else {

      lift.moveVelocity(0);

    }

    /*else if ( left.isPressed() ) {

      lift_PID(900);
      printf("done - up 900");

    } else if ( right.isPressed() ) {

      lift_PID(-900);
      printf("done - down 900");

    }
    */

    delay(20);

  }

}
