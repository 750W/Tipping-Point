#include "config.h"

void front_clamp () {

  contract_piston(100);

}

void front_unclamp () {

  extend_piston(100);

}

void back_clamp () {

  back_intake.moveVoltage(-4000);
  delay(200);

}

void back_unclamp () {

  back_intake.moveVoltage(4000);
  delay(200);

}

void extend_piston (int time) {

  piston.set_value(true);
  delay(time);

}

void contract_piston(int time){

  piston.set_value(false);
  delay(time);

}
