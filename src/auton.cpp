#include "main.h"
#include "config.h"
using namespace okapi;

void mbl_goal () {

  chassis -> setMaxVelocity (150);
  int count = 0;

  while ( !back_bumperswitch.isPressed() && count < 80 ) {

    move_dist (150, 25);
    count += 25;

  }
  stop ();

  for (int i = 0; i < 40; i++)
  back_clamp ();
  stop ();

  chassis -> setMaxVelocity (-150);

  if ( 15000 - (2 * count) > 0 ) {
    move_dist ( -150, 15000 - (2 * count) );
    stop ();
  }
  stop ();

  chassis -> setMaxVelocity (200);
  stop ();

}
//Gets both middle/neutral mobile goals with the both starting on the right side
void both_mobile_goals_right(){

}

//Gets both middle/neutral mobile goals with the both starting on the left side
void both_mobile_goals_left(){

}

//Gets a win point by scoring on both alliance goals and moving one of them out the win point line --- bot starts on the left side.
void both_win_points_left(){


}

//Gets a win point by scoring on both alliance goals and moving one of them out the win point line --- bot starts on the right side.
void both_win_points_right(){

}

//Scores in one of the alliance mobile goals and depending on where we are, also moves the allaince goal out of the win point line. --- bot starts on the right side.
void right_win_point () {
  chassis -> setMaxVelocity (40);
  int count = 0;
  while ( !back_bumperswitch.isPressed() && count < 80 ){
    move_dist (40, 25);
    count += 25;
  }
  stop ();
  for (int i = 0; i < 40; i++)
  front_clamp ();
  stop ();
  chassis -> setMaxVelocity (-40);
  if (15000 - (2 * count) > 0) {
    move_dist (-40, 15000 - (2 * count) );
    stop ();
  } else {
    move_dist (-40, 15000 - (2 * count) * -1);
    stop ();
  }
  chassis -> setMaxVelocity (200);
  stop ();
}

//Scores in one of the alliance mobile goals and depending on where we are, also moves the allaince goal out of the win point line. --- bot starts on the left side.
void left_win_point () {
  chassis -> setMaxVelocity (40);
  float count = 0;
  while ( !back_bumperswitch.isPressed() ) {
    move_dist (40, 25);
    count += 25;
  }
  stop ();
  for (int i = 0; i < 40; i++)
  back_clamp ();
  stop ();
  back_unclamp ();
  stop ();
  chassis -> setMaxVelocity (-60);
  float time = 60.0 / (40.0 * count);
  if (15000 - (count + time) > 0) {
    move_dist (-60, 15000 - (count + time));
    stop ();
  }
  chassis -> setMaxVelocity (200);
  stop ();
}

void new_auton_trial () {
  float count = 0;
  chassis -> setMaxVelocity (180);
  while ( !back_bumperswitch.isPressed() ) {
    move_dist (180, 25);
    count += 25;
  }
  move_dist (-180, count / 2);
  turn_cw (180, 25);
  count = 0;
  while ( !back_bumperswitch.isPressed() ) {
    move_dist (180, 25);
    count += 25;
  }
  move_dist (-180, count / 2);
}

void winPointAutonRight(){
  int degreesToMobileGoal = 50;
  //Step 1
  turn_cw_degrees(10,degreesToMobileGoal,1,25);
  //Steps 2, 3, 4
  right_win_point();
  //Step 4.5
  move_dist(40,50);
  stop();
  //Step 5
  turn_cw_degrees(10,90-degreesToMobileGoal,1,25);
  //Step 6
  int Ishaan5HeadCalc= 500; //random arbitrary num
  int x = 0;
  while(x < Ishaan5HeadCalc){
    //same move_dist parameters as other auton
    move_dist(40, 25);
    //change iteration based on what units the distance is in versus the speed at "40"
    x += 25;
  }
  stop();
  //again, all arbitrary/random parameters from before
//turn to face wall
  turn_ccw_degrees(10,90,1,25);
  //move up to align with mobile goal
  move_dist(40,50);
  stop();
  //turn to face mobile goal
  turn_ccw_degrees(10,90,1,25);
  //move to reach mobile goal
  move_dist(40,50);

  //clamp closing code copied from above
  //should score on second mobile goal
  for(int i = 0; i < 40; i++)
  front_clamp();
  stop();
  front_unclamp();
  stop();

}


/*
go straight;
grab neutral mogol(yellow one) with front intake (front is now the side with the lift );
back up x amount idk just put some random num lol;
turn 90 degrees counterclockwise (so that the back of our bot faces the alliance mogol);
drive backward a lil;
put back clamp down;
move forward a lil to clear alliance mogol from win point line
*/
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
  while ( !back_bumperswitch.isPressed() );
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

/*
void auton(){
  while((int)ultraLeft.controllerGet() != (int)ultraRight.controllerGet()){
    if((int)ultraLeft.controllerGet() > (int)ultraRight.controllerGet()){
      fR.moveVelocity(5);
      bR.moveVelocity(5);
      delay(25);
    }
    else if((int)ultraLeft.controllerGet() < (int)ultraRight.controllerGet()){
      fL.moveVelocity(5);
      bL.moveVelocity(5);
      delay(25);
    }
  }

  while((int)ultraLeft.controllerGet() != (int)ultraRight.controllerGet()){
    if((int)ultraLeft.controllerGet() > (int)ultraRight.controllerGet()){
      fR.moveVelocity(5);
      bR.moveVelocity(5);
      delay(25);
    }
    else if((int)ultraLeft.controllerGet() < (int)ultraRight.controllerGet()){
      fL.moveVelocity(5);
      bL.moveVelocity(5);
      delay(25);
    }
  }

    chassis->setMaxVelocity(60);
    float count = 0;
    while(!intakeLimitSwitch.isPressed()){
      moveDistance(60, 25);
      count += 25;
    }
    stop();
    for(int i = 0; i < 10; i++)
    frontIntakeClampDown();
    stop();
    chassis->setMaxVelocity(-60);
    moveDistance(-60, count*(float)3/4);
    stop();
    frontIntakeUp();
    stop();
    chassis->setMaxVelocity(60);
    turn_ccw(75);
    moveDistance(60, count*(float)1/2);
    turn_cw(count*(float)1/4);
    count = 0;
    while(!intakeLimitSwitch.isPressed()){
      moveDistance(60, 25);
      count += 25;
    }
    chassis->setMaxVelocity(-60);
    moveDistance(-60, count*(float)3/4);
    stop();
    frontIntakeUp();
    stop();
    moveDistance(-60, count*(float)1/4);
    stop();

    chassis->setMaxVelocity(150);
}
<<<<<<< HEAD

void(){

}
=======
*/
