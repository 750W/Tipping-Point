#include "config.h"
using namespace okapi;

void drive_PID (double dist) {

  double errorL, errorR, kP, velocityL, velocityR;

  double total_errorL, total_errorR, kI;

  double prev_errorL, prev_errorR, kD, derivativeL, derivativeR;

  int l_begpos, r_begpos, lpos, rpos, desired_val;

  double half;

  int diff;

  r_begpos = (int)drive_fR.getPosition();
  l_begpos = (int)drive_fL.getPosition();

  diff =  r_begpos - l_begpos;

  desired_val = dist * 100 / (2 * 3.14 * 2.0) * 360.0;

  if ( l_begpos != desired_val && r_begpos != desired_val ) {

    kP = 0.3;
    kD = 0;

    prev_errorL = 0.0;
    prev_errorR = 0.0;
    desired_val = dist * 100 / ( 2 * 3.14 * 2.0 ) * 360.0;

    front_drive.tarePosition();

    r_begpos = (int) drive_fR.getPosition();
    l_begpos = (int) drive_fL.getPosition();

    diff =  r_begpos - l_begpos;

    lpos = 0;
    rpos = 0;

    while ( desired_val != lpos && desired_val != rpos ) {

      rpos = (int) drive_fR.getPosition() + -1 * r_begpos;
      lpos = (int) drive_fL.getPosition() + -1 * l_begpos;

      errorL = desired_val - lpos;
      errorR = desired_val - rpos;

      derivativeL = errorL - prev_errorL;
      derivativeR = errorR - prev_errorR;

      velocityL = (errorL * kP + derivativeL * kD);
      velocityR = (errorR * kP + derivativeR * kD);

      int sign = 0;

      if ( velocityL > 150 ) {

        velocityL = 150;
        sign++;

      } else if ( velocityL < -150 ) {

        velocityL = -150;
        sign--;

      }

      if ( velocityR > 150 ) {

        velocityR = 150;
        sign++;

      } else if ( velocityR < -150 ) {

        velocityR = -150;
        sign--;

      }

      if ( (sign > 0 && velocityL < 10 && velocityR < 10) || (sign < 0 && velocityL > -10 && velocityR > -10) )
      break;

      move_dist(velocityL - diff, velocityR + diff);

      prev_errorL = errorL;
      prev_errorR = errorR;

      delay(20);

    }

  }

}

void turn_PID(double dist){

    double errorL, errorR, kP, velocityL, velocityR;

    double total_errorL, total_errorR, kI;

    double prev_errorL, prev_errorR, kD, derivativeL, derivativeR;

    int l_begpos, r_begpos, lpos, rpos, desired_val;

    r_begpos = (int)drive_fR.getPosition();
    l_begpos = (int)drive_fL.getPosition();

    if ( l_begpos != (int) dist && r_begpos != (int) dist ) {

      kP = 0.1;
      kI = 0.0;
      kD = 0.0;

      prev_errorL = 0.0;
      prev_errorR = 0.0;
      desired_val = (int) dist;

      drive_tarePos();
      r_begpos = (int) drive_fR.getPosition();
      l_begpos = (int) drive_fL.getPosition();

      lpos = 0;
      rpos = 0;

      while ( desired_val != lpos && desired_val != rpos ) {

        rpos = (int) drive_fR.getPosition() + -1 * r_begpos;
        lpos = (int) drive_fL.getPosition() + -1 * l_begpos;

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

        velocityL = (errorL * kP + total_errorL * kI + derivativeL * kD);
        velocityR = (errorR * kP + total_errorR * kI + derivativeR * kD);

        if ( velocityL > 150 ) {

          velocityL = 150;

        } else if ( velocityR > 150 ) {

          velocityR = 150;

        } else if ( velocityL < -150 ) {

          velocityL = -150;

        } else if ( velocityR < -150 ) {

          velocityR = -150;

        }

        drive_fL.moveVelocity(velocityL);
        drive_fR.moveVelocity(velocityR);
        drive_bL.moveVelocity(velocityL);
        drive_bR.moveVelocity(velocityR);

        prev_errorL = errorL;
        prev_errorR = errorR;

        delay(20);

      }

    }

    drive_fL.moveVelocity(0);
    drive_fR.moveVelocity(0);
    drive_bL.moveVelocity(0);
    drive_bR.moveVelocity(0);

    delay(20);

}

void lift_PID (int rev) {

  double errorL, errorR, kP, velocityL, velocityR;

  double total_errorL, total_errorR, kI;

  double prev_errorL, prev_errorR, kD, derivativeL, derivativeR;

  int l_begpos, r_begpos, lpos, rpos, desired_val;

  r_begpos = (int)liftR.getPosition();
  l_begpos = (int)liftL.getPosition();

  if ( l_begpos != rev && r_begpos != rev ) {

    kP = 0.3;
    kI = 0.2;
    kD = 0.3;

    prev_errorL = 0.0;
    prev_errorR = 0.0;
    desired_val = rev;

    lift.tarePosition();

    r_begpos = (int)liftR.getPosition();
    l_begpos = (int)liftL.getPosition();

    lpos = 0;
    rpos = 0;
    int sign = 0;

    while (desired_val != lpos && desired_val != rpos) {

      rpos = (int) liftR.getPosition() + -1 * r_begpos;
      lpos = (int) liftL.getPosition() + -1 * l_begpos;

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

      velocityL = (errorL * kP + total_errorL * kI + derivativeL * kD);
      velocityR = (errorR * kP + total_errorR * kI + derivativeR * kD);

      if ( velocityL > 80 ) {

        velocityL = 80;
        sign++;

      } else if ( velocityR > 80 ) {

        velocityR = 80;
        sign++;

      } else if ( velocityL < -80 ) {

        velocityL = -80;
        sign--;

      } else if ( velocityR < -80 ) {

        velocityR = -80;
        sign--;

      }

      if ( (sign > 0 && velocityL < 10 && velocityR < 10) || (sign < 0 && velocityL > -10 && velocityR > -10) )
      break;

      liftL.moveVelocity(velocityL);
      liftR.moveVelocity(velocityR);

      prev_errorL = errorL;
      prev_errorR = errorR;
      
      delay(20);

    }

  }

  lift.moveVelocity(0);
  delay(20);
}
