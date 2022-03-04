#include "config.h"

void lift_up () {

  lift.moveVelocity(100);
  delay(25);

}

void lift_down () {

  lift.moveVelocity(-100);
  delay(25);
  
}
