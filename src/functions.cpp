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
  lift_PID(1850);
}

void lift_down(){
  lift_PID(-3);
}

void lift_PID(int rev){

  double errorL, errorR, kP, powerL, powerR;
  double total_errorL, total_errorR, kI;
  double prev_errorL, prev_errorR, kD, derivativeL, derivativeR;
  int l_begpos, r_begpos, lpos, rpos, desired_val;

  kP = 0.1;
  kI = 0.0;
  kD = 0.0;

  prev_errorL = 0.0;
  prev_errorR = 0.0;
  desired_val = rev;

  lift.tarePosition();
  r_begpos = (int)liftR.getPosition();
  l_begpos = (int)liftL.getPosition();

  lpos = 0;
  rpos = 0;

  while (desired_val != lpos && desired_val != rpos) {

    rpos = (int)liftR.getPosition() + -1 * r_begpos;
    lpos = (int)liftL.getPosition() + -1 * l_begpos;

    printf("RPOS: %d\n", rpos);
    printf("LPOS: %d\n", lpos);

    errorL = abs(desired_val - lpos);
    errorR = abs(desired_val - rpos);
    total_errorL += errorL;
    total_errorR += errorR;

    if(errorL == 0 || lpos < desired_val){
      total_errorL = 0;
    }

    if(errorR == 0 || rpos < desired_val){
      total_errorR = 0;
    }

    derivativeL = errorL - prev_errorL;
    derivativeR = errorR - prev_errorR;

    powerL = (errorL * kP + total_errorL * kI + derivativeL * kD);
    powerR = (errorR * kP + total_errorR * kI + derivativeR * kD);

    if(powerL > 80){
      powerL = 80;
    }

    if(powerR > 80){
      powerR = 80;
    }

    liftL.moveVelocity(powerL);
    liftR.moveVelocity(powerR);

    prev_errorL = errorL;
    prev_errorR = errorR;
    delay(20);
  }

  lift.moveVelocity(0);
  delay(20);
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
