#include "config.h"

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
