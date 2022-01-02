#include "main.h"
#include "config.h"
#include "math.h"

void move_dist (float spd, int time) {

  drive_fL.moveVelocity(spd);
  drive_fR.moveVelocity(spd);
  drive_bL.moveVelocity(spd);
  drive_bR.moveVelocity(spd);
  delay(time);

}

void front_clamp () {

  front_intake.moveVoltage(8000);
  delay (75) ;

}

void front_unclamp () {

  front_intake.moveVoltage(-8000);
  delay(50);

}

void back_clamp () {

  back_intake.moveVoltage(8000);
  delay(75);

}

void back_unclamp () {

  back_intake.moveVoltage(-8000);
  delay(50);

}

void lift_up () {

  lift_PID(1000);

}

void lift_down () {

  lift_PID(-1000);

}

void lift_PID (int rev) {

  double errorL, errorR, kP, powerL, powerR;
  double total_errorL, total_errorR, kI;
  double prev_errorL, prev_errorR, kD, derivativeL, derivativeR;
  int l_begpos, r_begpos, lpos, rpos, desired_val;

  r_begpos = (int)liftR.getPosition();
  l_begpos = (int)liftL.getPosition();

  if ( l_begpos != rev && r_begpos != rev ) {

    kP = 0.0;
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

    while ( desired_val != lpos && desired_val != rpos ) {

      rpos = (int)liftR.getPosition() + -1 * r_begpos;
      lpos = (int)liftL.getPosition() + -1 * l_begpos;

      errorL = desired_val - lpos;
      errorR = desired_val - rpos;
      total_errorL += errorL;
      total_errorR += errorR;

      if ( errorL == 0 || lpos < desired_val ) {
        total_errorL = 0;
      }

      if ( errorR == 0 || rpos < desired_val ) {
        total_errorR = 0;
      }

      derivativeL = errorL - prev_errorL;
      derivativeR = errorR - prev_errorR;

      powerL = (errorL * kP + total_errorL * kI + derivativeL * kD);
      powerR = (errorR * kP + total_errorR * kI + derivativeR * kD);

      if ( powerL > 80 ) {

        powerL = 80;

      } else if ( powerR > 80 ) {

        powerR = 80;

      } else if ( powerL < -80 ) {

        powerL = -80;

      } else if ( powerR < -80 ) {

        powerR = -80;

      }

      liftL.moveVelocity(powerL);
      liftR.moveVelocity(powerR);

      //printf ("Error: %f, %f", errorL, errorR) ;
      //printf ("Power: %f, %f", powerL, powerR) ;

      prev_errorL = errorL;
      prev_errorR = errorR;
      delay(20);

    }

  }

  lift.moveVelocity(0);
  delay(20);
}

void stop () {

  drive_fL.moveVelocity(0);
  drive_fR.moveVelocity(0);
  drive_bL.moveVelocity(0);
  drive_bR.moveVelocity(0);

  lift.moveVelocity(0);
  front_intake.moveVoltage(0);
  back_intake.moveVoltage(0);

}

void turn_cw (float spd, int time) {

  drive_fL.moveVelocity(spd);
  drive_fR.moveVelocity(0);
  drive_bL.moveVelocity(spd);
  drive_bR.moveVelocity(spd);

  delay(time);
  stop();

}

void turn_ccw (float spd, int time) {

  drive_fL.moveVelocity(0);
  drive_fR.moveVelocity(spd);
  drive_bL.moveVelocity(0);
  drive_bR.moveVelocity(spd);

  delay(time);
  stop();

}

void drive_PID (double dist) {

  double errorL, errorR, kP, powerL, powerR;
  double total_errorL, total_errorR, kI;
  double prev_errorL, prev_errorR, kD, derivativeL, derivativeR;
  int l_begpos, r_begpos, lpos, rpos, desired_val;

  r_begpos = (int)drive_fR.getPosition();
  l_begpos = (int)drive_fL.getPosition();

  if ( l_begpos != (int)dist && r_begpos != (int)dist ) {

    kP = 0.0;
    kI = 0.0;
    kD = 0.0;

    prev_errorL = 0.0;
    prev_errorR = 0.0;
    desired_val = (int)dist;

    drive_tarePos();
    r_begpos = (int)drive_fR.getPosition();
    l_begpos = (int)drive_fL.getPosition();

    lpos = 0;
    rpos = 0;

    while ( desired_val != lpos && desired_val != rpos ) {

      rpos = (int)drive_fR.getPosition() + -1 * r_begpos;
      lpos = (int)drive_fL.getPosition() + -1 * l_begpos;

      errorL = desired_val - lpos;
      errorR = desired_val - rpos;
      total_errorL += errorL;
      total_errorR += errorR;

      if ( errorL == 0 || lpos < desired_val ) {
        total_errorL = 0;
      }

      if ( errorR == 0 || rpos < desired_val ) {
        total_errorR = 0;
      }

      derivativeL = errorL - prev_errorL;
      derivativeR = errorR - prev_errorR;

      powerL = (errorL * kP + total_errorL * kI + derivativeL * kD);
      powerR = (errorR * kP + total_errorR * kI + derivativeR * kD);

      if ( powerL > 150 ) {

        powerL = 150;

      } else if ( powerR > 150 ) {

        powerR = 150;

      } else if ( powerL < -150 ) {

        powerL = -150;

      } else if ( powerR < -150 ) {

        powerR = -150;

      }

      liftL.moveVelocity(powerL);
      liftR.moveVelocity(powerR);

      //printf ("Error: %f, %f", errorL, errorR) ;
      //printf ("Power: %f, %f", powerL, powerR) ;

      prev_errorL = errorL;
      prev_errorR = errorR;
      delay(20);

    }

  }

  lift.moveVelocity(0);
  delay(20);

}

void drive_tarePos() {

  drive_fR.tarePosition();
  drive_bR.tarePosition();
  drive_fL.tarePosition();
  drive_bL.tarePosition();

}
