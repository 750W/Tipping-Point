#include "main.h"
#include "config.h"
#include "math.h"
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
  lift_PID(-1852);
  delay(30); //experiment with this value
}

void lift_down(){
  lift_PID(1852);
  delay(30); //experiment with this value
}

void lift_PID(int deg){
  lift.moveVelocity(100);
  delay(25);
  /*
  float error, kP, desired_val, power, pos;
  float total_error, kI;
  float prev_error, kD, derivative;
  kP = 0.2;
  kI = 0.1;
  kD = 0.1;
  desired_val = deg;
  prev_error = 0.0;

  lift.tarePosition();
  while ((int)desired_val != (int)pos) {
    printf("%d\n", liftR.getPosition());
    printf("%d\n", liftL.getPosition());
    pos = (liftR.getPosition() + liftL.getPosition()) / 2.0;
    error = desired_val - pos;
    printf("%d\n", error);
    //total_error += error;
    //if(error == 0 || pos > desired_val){
    //  total_error = 0;
    //}
    //derivative = prev_error - error;
    power = error * kP;
    //+ total_error * kI + derivative * kD;
    lift.moveVelocity(power);
    //prev_error = error;
    delay(20);
  }
  */
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

void turn_cw (float spd, int time){
  drive_fL.moveVelocity(spd);
  drive_fR.moveVelocity(0);
  drive_bL.moveVelocity(spd);
  drive_bR.moveVelocity(spd);
  delay(time);
  stop();
}
void turn_ccw (float spd, int time){
  drive_fL.moveVelocity(0);
  drive_fR.moveVelocity(spd);
  drive_bL.moveVelocity(0);
  drive_bR.moveVelocity(spd);
  delay(time);
  stop();
}

void drive_PID (float dist){
  float error, velocity, drive_fL_position, drive_fR_position, desired_value, avg_position, kP;
  float prev_error, kD, derivate;

  kP = 0.1;
  kD = 0.1;
  prev_error = 0.0;
  desired_value = round(1000 * (dist / (4 * 2.54 * 3.14)) / 1000);
  drive_fL_position = drive_fL.getPosition();
  drive_fR_position = drive_fR.getPosition();
  avg_position = (drive_fR_position + drive_fL_position) / 2.0;

  while (avg_position != desired_value){
    //dist = sensor.getValue();
    desired_value = round(1000 * (dist / (4 * 2.54 * 3.14)) / 1000);
    drive_fL_position = drive_fL.getPosition();
    drive_fR_position = drive_fR.getPosition();
    avg_position = (drive_fL_position + drive_fR_position) / 2.0;
    error = desired_value - avg_position;
    derivate = prev_error - error;
    velocity = error * kP + derivate * kD;
    move_dist(velocity, 50);
    prev_error = error;
    delay(20);
  }

  delay(20);
}
