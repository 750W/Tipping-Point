#include "config.h"

void ring_forward(){

  ring_intake.moveVelocity(80);

}

void ring_reverse(){

  ring_intake.moveVelocity(-80);

}

void ring_stop(){

  ring_intake.moveVoltage(0);

}
