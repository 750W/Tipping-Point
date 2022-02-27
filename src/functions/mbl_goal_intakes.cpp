#include "config.h"

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

  extend_piston(100);

}

void back_auto_clamp () {

  back_intake.moveVoltage(-8000);
  delay(100);
  back_intake.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);

}

void back_unclamp () {

  contract_piston(100);

}

void back_auto_unclamp () {

  back_intake.moveVoltage(8000);
  delay(400);
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
