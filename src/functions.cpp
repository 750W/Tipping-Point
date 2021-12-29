#include "main.h"
#include "config.h"
void move_dist(float spd, int time){
  drive_fL.moveVelocity(spd);
  drive_fR.moveVelocity(spd);
  drive_bL.moveVelocity(spd);
  drive_bR.moveVelocity(spd);
  delay(time);
}
void front_clamp(){
  front_intake.moveVoltage(8000);
  delay(75); //experiment with this value TEST
}
void front_unclamp(){
  front_intake.moveVoltage(-8000);
  delay(50); //experiment with this value
}
void back_clamp(){
  back_intake.moveVoltage(8000);
  delay(75);
}
void back_unclamp(){
  back_intake.moveVoltage(-8000);
  delay(50);
}
void lift_up(){
  lift.moveVelocity(75);
  delay(30); //experiment with this value
}
void lift_down(){
  lift.moveVelocity(-100);
  delay(30); //experiment with this value
}
void stop(){
  drive_fL.moveVelocity(0);
  drive_fR.moveVelocity(0);
  drive_bL.moveVelocity(0);
  drive_bR.moveVelocity(0);
  lift.moveVelocity(0);
  front_intake.moveVoltage(0);
  back_intake.moveVoltage(0);
}

void turn_cw_degrees(float spd, int degrees, int delayBetween, int time){
  //should set whatever current angle is to be 0 degrees
  imu.reset();
  //keeps rotating until rotation reaches inputed value
  while(imu.get_rotation()>=degrees){
    drive_fL.moveVelocity(spd);
    drive_fR.moveVelocity(0);
    drive_bL.moveVelocity(spd);
    drive_bR.moveVelocity(0);
    //small delay between each loop, to be safe
    delay(delayBetween);
  }
  //delay bc other turn fuctions had one
  delay(time);
  stop();
}
void turn_ccw_degrees(float spd, int degrees, int delayBetween, int time){
//same as turn_degrees_cw
  imu.reset();
  //as far as i know, calling get_rotation after turning ccw return negative
  //so, abs val is taken so that same logic as before applies
  while(abs(imu.get_rotation())>=degrees){
    drive_fL.moveVelocity(0);
    drive_fR.moveVelocity(spd);
    drive_bL.moveVelocity(0);
    drive_bR.moveVelocity(spd);
    delay(delayBetween);
  }
  delay(time);
  stop();
}

void turn_cw(float spd, int time){
  drive_fL.moveVelocity(spd);
  drive_fR.moveVelocity(0);
  drive_bL.moveVelocity(spd);
  drive_bR.moveVelocity(spd);
  delay(time);
  stop();
}
void turn_ccw(float spd, int time){
  drive_fL.moveVelocity(0);
  drive_fR.moveVelocity(spd);
  drive_bL.moveVelocity(0);
  drive_bR.moveVelocity(spd);
  delay(time);
  stop();
}

void motionPID(float dist){

}
/*
void motionPID(float dist){
  float error, integral, prevError, derivative = 0;
  float power = 100;
  while((int)pot.controllerGet() != (int)dist){
    error = dist - pot.controllerGet();
    integral += error;
    if(error == 0 || (int)pot.controllerGet() == (int)dist){
      integral = 0;
    }
    if(pot.controllerGet() > 10){ //if error is outside of useful range
      integral = 0;
    }
    derivative = integral - prevError;
    prevError = error;
    power = error*kP + integral*kI + derivative*kD;
    delay(15);
    moveDistance(power, 15);
  }
}
*/
