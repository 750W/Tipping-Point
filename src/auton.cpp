#include "main.h"
#include "config.h"
using namespace okapi;

void mbl_goal(){
  chassis->setMaxVelocity(150);
  int count = 0;
  while(!back_bumperswitch.isPressed() && count < 80){
    move_dist(150, 25);
    count += 25;
  }
  stop();
  for(int i = 0; i < 40; i++)
  back_clamp();
  stop();
  chassis->setMaxVelocity(-150);
  if(15000-(2*count) > 0){
    move_dist(-150, 15000-(2*count));
    stop();
  }
  stop();
  chassis->setMaxVelocity(200);
  stop();
}

void right_win_point(){
  chassis->setMaxVelocity(40);
  int count = 0;
  while(!back_bumperswitch.isPressed() && count < 80){
    move_dist(40, 25);
    count += 25;
  }
  stop();
  for(int i = 0; i < 40; i++)
  front_clamp();
  stop();
  chassis->setMaxVelocity(-40);
  if(15000-(2*count) > 0){
    move_dist(-40, 15000-(2*count));
    stop();
  }
  else{
    move_dist(-40, 15000-(2*count)*-1);
    stop();
  }
  chassis->setMaxVelocity(200);
  stop();
}

void left_win_point(){
  chassis->setMaxVelocity(40);
  float count = 0;
  while(!back_bumperswitch.isPressed()){
    move_dist(40, 25);
    count += 25;
  }
  stop();
  for(int i = 0; i < 40; i++)
  back_clamp();
  stop();
  back_unclamp();
  stop();
  chassis->setMaxVelocity(-60);
  float time = 60.0/(40.0*count);
  if(15000-(count + time) > 0){
    move_dist(-60, 15000-(count + time));
    stop();
  }
  chassis->setMaxVelocity(200);
  stop();
}

void new_auton_trial(){
  float count = 0;
  chassis->setMaxVelocity(180);
  while(!back_bumperswitch.isPressed()){
    move_dist(180, 25);
    count += 25;
  }
  move_dist(-180, count/2);
  turn_cw(180, 25);
  count = 0;
  while(!back_bumperswitch.isPressed()){
    move_dist(180, 25);
    count += 25;
  }
  move_dist(-180, count/2);
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
void auton_selector(){
  joystick.clear();
  delay(100);
  int j = 0;
  int pressed = 0;
  joystick.setText(0, 0, "X - mbl");
  joystick.setText(0, 1, "A - LWP");
  joystick.setText(0, 2, "Y - RWP");
  joystick.setText(0, 3, "B - None");  
  delay(100);
  i = 10;
  while (i != -10){
    if(back_bumperswitch.isPressed()){
      pressed = -1;
    }
    while(!pressed){
      if(x.isPressed()){
        i = 0;
        joystick.setText(0, 0, "mbl selected");
        pressed = 1;
        printf("x pressed");
      }
      else if(a.isPressed()){
        i = 1;
        joystick.setText(0, 0, "lwp selected");
        pressed = 1;
      }
      else if(y.isPressed()){
        i = 2;
        joystick.setText(0, 0, "rwp selected");
        pressed = 1;
      }
      else if(b.isPressed()){
        i = -1;
        joystick.setText(0, 0, "no auton selected");
        pressed = 1;
      }
      if(!pressed){
        i = -10;
      }
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
*/
