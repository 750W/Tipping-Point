#include "config.h"

void front_clamp () {

  contract_piston(100);

}

void front_unclamp () {

  extend_piston(100);

}

void back_down () {

  back_intake.moveVelocity(-100);
  delay(200);
  back_intake.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);

}

void back_up () {

  back_intake.moveVelocity(100);
  delay(800);
  back_intake.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);

}

void extend_piston (int time) {

  piston.set_value(true);
  delay(time);

}

void contract_piston(int time){

  piston.set_value(false);
  delay(time);

}
