#include "config.h"

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

void drive_tarePos() {

  drive_fR.tarePosition();
  drive_bR.tarePosition();
  drive_fL.tarePosition();
  drive_bL.tarePosition();

}

void move_dist_drive (double spdL, double spdR) {

  drive_fL.moveVelocity(spdL);
  drive_fR.moveVelocity(spdR);
  drive_bL.moveVelocity(spdL);
  drive_bR.moveVelocity(spdR);

  delay(40);

}

void move_dist (double spd, int time) {

  drive_fL.moveVelocity(spd);
  drive_fR.moveVelocity(spd);
  drive_bL.moveVelocity(spd);
  drive_bR.moveVelocity(spd);

  delay(time);

}

void front_clamp () {

  front_intake.moveVelocity(60);
  delay (100) ;
  front_intake.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);

}

void front_unclamp () {

  front_intake.moveVelocity(-60);
  delay(100);

}

void back_clamp () {

  back_intake.moveVoltage(-8000);
  delay(200);

}

void back_auto_clamp () {

  back_intake.moveVoltage(-8000);
  delay(400);
  back_intake.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);

}

void back_unclamp () {

  back_intake.moveVoltage(16000);
  delay(200);

}

void back_auto_unclamp () {

  back_intake.moveVoltage(8000);
  delay(400);
  back_intake.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);

}

void lift_up () {

  lift.moveVelocity(100);

}

void lift_down () {

  lift.moveVelocity(-100);

}

void turn_cw (float spd, int time) {

  drive_fL.moveVelocity(spd);
  drive_fR.moveVelocity(0);
  drive_bL.moveVelocity(spd);
  drive_bR.moveVelocity(spd);

  delay(time);

}

void turn_ccw (float spd, int time) {

  drive_fL.moveVelocity(0);
  drive_fR.moveVelocity(spd);
  drive_bL.moveVelocity(0);
  drive_bR.moveVelocity(spd);

  delay(time);

}

void extend_piston (int time) {
    piston.set_value(true);
    delay(time);
}

void contract_piston(int time){
    piston.set_value(false);
    delay(time);
}
