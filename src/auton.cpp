#include "config.h"
using namespace okapi;

void left_win_point() {

  for(int i = 0; i < 3; i++)
  back_down();
  delay(25);

  for(int i = 0; i < 3; i++)
  back_up();
  delay(25);

}

void right_win_point() {

  chassis->setMaxVelocity(200);
  int count = 0;

  while(back_bumperswitch.isPressed()){
    move_dist(100, 25);
    count += 25;
  }

  front_clamp();
  move_dist(-100, count);

}

void mbl_goal() {

  chassis->setMaxVelocity(200);
  int count = 0;

  while(back_bumperswitch.isPressed()){
    move_dist(180, 25);
    count += 25;
  }

  front_clamp();
  move_dist(-200, count);

}

void both_win_points_left() {

  chassis->setState({0_in, 0_in, 0_deg});

  for(int i = 0; i < 3; i++)
  back_down();
  delay(25);

  for(int i = 0; i < 3; i++)
  back_up();
  delay(25);

  chassis->turnToAngle(-45_deg);
  delay(25);
  move_dist(-100, 1000);
  delay(40);

  chassis->turnToAngle(45_deg);
  move_dist(-150, 2000);
  move_dist(0, 25);
  back_down();
  move_dist(150, 200);
  move_dist(0, 25);

}

void both_neutral_goals_right() {

  chassis->setState({0_in, 0_in, 0_deg});
  drive_PID(100.0);
  front_clamp();
  chassis->turnToAngle(-90_deg);
  move_dist(200, 300);

  back_up();
  chassis->turnToAngle(0_deg);
  move_dist(-200, 500);

}

void auton_selector () {

  joystick.clear ();
  delay (100);

  int j = 0;
  int pressed = 0;

  joystick.setText (0, 0, "X - mbl");
  joystick.setText (1, 0, "A - LWP");
  joystick.setText (2, 0, "Y - RWP");
  joystick.setText (3, 0, "B - None");
  delay (100);

  i = -99;

  while (i == -99) {

    if (x.isPressed() ) {

      i = 0;
      joystick.setText (0, 0, "mbl selected");

    } else if ( a.isPressed() ) {

      i = 1;
      joystick.setText (0, 0, "lwp selected");

    } else if ( y.isPressed() ) {

      i = 2;
      joystick.setText (0, 0, "rwp selected");

    } else if ( b.isPressed() ) {

      i = -1;
      joystick.setText (0, 0, "no auton selected");

    }

  }

}

void prog_skills() {
  int x = 500;
  int y = 250;
  //start red side
  chassis->setState({0_in, 0_in, 0_deg});
  move_dist(-100, 500);
  back_up();
  //clamp onto the alliance goal

  ring_forward();
  //turn on ring intake

  move_dist(100, 500);
  chassis->turnToAngle(90_deg);


  move_dist(100,x);
  front_clamp();
  move_dist(100,x);
  front_unclamp();
  back_down();

  chassis->turnToAngle(180_deg);
  move_dist(100,y);
  chassis->turnToAngle(-90_deg);

  move_dist(100,x);
  front_clamp();
  move_dist(100,x);
  front_unclamp();

  chassis->turnToAngle(180_deg);
  move_dist(100,y);
  chassis->turnToAngle(90_deg);

  move_dist(100,x);
  front_clamp();
  move_dist(100,x);
  front_unclamp();

}

void stop () {

  drive_fL.moveVelocity(0);
  drive_fR.moveVelocity(0);
  drive_bL.moveVelocity(0);
  drive_bR.moveVelocity(0);

  lift.moveVelocity(0);
  front_intake.moveVoltage(0);
  back_intake.moveVoltage(0);

  delay(600);

}
