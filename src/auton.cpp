#include "config.h"
using namespace okapi;

void right_win_point () {

  chassis -> setMaxVelocity (400);
  int count = 0;

  while ( !back_bumperswitch.isPressed()) {
    move_dist(-180, 25);
    count += 25;
  }

  back_intake.moveVoltage(16000);
  delay(400);

  back_intake.moveVoltage(8000);
  move_dist(200, count);
  stop ();

  chassis -> setMaxVelocity (180);
  stop ();

}

void left_win_point () {

  chassis -> setMaxVelocity (200);
  int count = 0;

  while ( !back_bumperswitch.isPressed()) {
    move_dist(-40, 25);
    count += 25;
  }
  stop();

  move_dist(100, 75);
  stop();

  back_clamp();
  delay(800);
  stop();

  back_unclamp();
  delay(800);
  stop();

  move_dist(200, count);
  stop ();

  chassis -> setMaxVelocity (200);
  stop ();

}

void mbl_goal () {

  chassis -> setMaxVelocity (600);
  int count = 0;

  while ( !back_bumperswitch.isPressed()) {
      move_dist (200, 25);
      count += 25;
      if(count >= 1000)
        move_dist (50, 25);
  }

  front_clamp();
  delay(25);

  move_dist(-200, count);
  stop ();

  chassis -> setMaxVelocity (600);
  stop ();

}

void both_mobile_goals_right(){

  chassis -> setMaxVelocity (150);
  int count = 0;

  while ( !back_bumperswitch.isPressed()) {

    move_dist(150, 25);
    count += 25;

    if(count >= 15000)
    break;

  }

  stop();

  if(count < 15000){

    for (int i = 0; i < 40; i++)
    back_clamp();
    stop();

    chassis -> setMaxVelocity (-150);

    move_dist(-150, count/2);
    count += count/2;

    turn_ccw(100, 10); //change this value accordingly
    count += 10;

    move_dist(-150, 10); //change this value accordingly
    count += 10;

    if(count < 15000){

      for (int i = 0; i < 10; i++)
      front_clamp();
      stop();
      move_dist(-150, 75); //change this value accordingly

    }

    stop ();
  }
}

void both_mobile_goals_left(){

}

void both_win_points_left(){
    //Step 1
    turn_cw(90, 40); //TODO: turn_cw_PID not yet made
    //Step 2
    back_clamp ();
    stop ();

    back_unclamp ();
    stop ();
    //Step 2.5: Back up before turning to avoid moving mobile goal
    move_dist(-40,70);
    //Step 3
    turn_cw(90, 40);
    //Step 4
    move_dist(40,70);
    //Step 5
    turn_cw(90, 40);
    //Step 6
    auton_state = true;
    double currentPos = getCurrentPosition();
    double distance = 48 + currentPos;//assumes it returns inches

    while (distance > currentPos) {

        move_dist (40, 25);
        currentPos = getCurrentPosition();

    }

    auton_state = false;
    //Step 7
    front_clamp();
    stop();

    front_unclamp();
    stop();
    //Step 8
    move_dist(-40, 70);
    //Step 9 - To return it to original position in step 1
    turn_cw(-90, 40);

}

//Gets a win point by scoring on both alliance goals and moving one of them out the win point line --- bot starts on the right side.
void both_win_points_right(){

    int degreesToMobileGoal = 50;
    //Step 1
    //currently assumes only parameter is degrees
    turn_cw(degreesToMobileGoal, 40); //TODO: turn_cw_PID not yet made
    //Steps 2, 3, 4
    mbl_goal();
    //Step 4.5
    move_dist(40,50);
    stop();
    //Step 5
    turn_cw_PID(degreesToMobileGoal);
    //Step 6
    auton_state = true;

    double currentPos = getCurrentPosition();
    double distance = 48 + currentPos;//assumes it returns inches

    while (distance > currentPos){

        move_dist (40, 25);
        currentPos = getCurrentPosition();

    }

    auton_state = false;
    stop();
    //Step 7
    //currently assumes only parameter is degrees
    turn_ccw_PID(90);
    //Step 8
    move_dist(40,50);
    stop();
    //Step 9
    turn_ccw_PID(90);
    //Optional Step 9.5 if Step 6 overestimates
    move_dist(40,50);
    //Step 10
    front_clamp();
    stop();

    front_unclamp();
    stop();
}

void right_win_point_mbl_goal(){
  //assuming that the bot is facing w the lift at the back
  chassis -> setMaxVelocity (150);
  int count = 0;

  while ( !back_bumperswitch.isPressed()) {
    move_dist(150, 25);
    count += 25;

    if(count >= 15000)
    break;

  }
  stop();

  if(count < 15000){

    for (int i = 0; i < 40; i++)
    back_clamp();
    stop();

    chassis -> setMaxVelocity (-150);

    move_dist(-150, count/2);
    count += count/2;

    turn_ccw(60, 50); //change this value accordingly
    count += 50;

    move_dist(-150, 10); //change this value accordingly
    count += 10;

    if(count < 15000){

      for (int i = 0; i < 10; i++)
      front_clamp();
      stop();

      move_dist(-150, 75);

    }

    stop ();
  }

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

  chassis->setState({0_in, 0_in, 0_deg});


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
