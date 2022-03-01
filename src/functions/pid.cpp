#include "config.h"
using namespace okapi;


void drive_PID (double dist) {

  okapi::MotorGroup left({drive_fL, drive_bL});
  okapi::MotorGroup right({drive_fR, drive_bR});

  left.tarePosition();
  double diff = -1*right.getPosition() - left.getPosition();

  printf("diff%f", diff);
  double desired_val = (30.0 / M_PI) * (1.0 / 4.0) * dist;

  double errorL = desired_val - left.getPosition();
  double kP = 0.155;
  double kD = 0.8;
  double velocityL = 200;

  double errorR = desired_val - right.getPosition();
  double velocityR = 200;

  double prev_errorR = 0.0;
  double prev_errorL = 0.0;

  double derivativeL = errorL - prev_errorL;
  double derivativeR = errorR - prev_errorR;

  while((int)desired_val != left.getPosition() && (int)desired_val != right.getPosition()) {

    errorL = desired_val - left.getPosition();
    errorR = desired_val - (right.getPosition() + diff);


    derivativeL = errorL - prev_errorL;
    derivativeR = errorR - prev_errorR;

    velocityL = errorL * kP + derivativeL * kD;
    velocityR = errorR * kP + derivativeR * kD;

    printf("error right: %f", errorR);
    printf("error left: %f", errorL);

    if(velocityL > 200) {

      velocityL = 200;

    } else if(velocityR > 200) {

      velocityL = 200;

    } else if(velocityL < 15) {

      break;

    } else if(velocityR < 15) {

      break;

    }

    left.moveVelocity(velocityL);
    right.moveVelocity(velocityR);
    delay(25);

    prev_errorR = errorR;
    prev_errorL = errorL;

  }

  left.moveVelocity(0);
  right.moveVelocity(0);

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

  double error, kP, velocity ;

  double total_error, kI;

  double prev_error, kD, derivative;

  int begpos, pos, desired_val;

  begpos = (int)lift.getPosition();

  if ( begpos != rev ) {

    kP = 0.3;
    kI = 0.2;
    kD = 0.3;

    prev_error = 0.0;
    desired_val = rev;

    lift.tarePosition();

    begpos = (int)lift.getPosition();

    pos = 0;

    int sign = 0;

    while (desired_val != pos) {

      pos = (int) lift.getPosition() + -1 * begpos;

      error = desired_val - pos;

      total_error += error;

      if ( error == 0 || pos < desired_val ) {

        total_error = 0;

      }

      derivative = error - prev_error;

      velocity = (error * kP + total_error * kI + derivative * kD);

      if ( velocity > 80 ) {

        velocity = 80;
        sign++;

      } else if ( velocity < -80 ) {

        velocity = -80;
        sign--;

      }

      if ( (sign > 0 && velocity < 10) || (sign < 0 && velocity > -10) )
      break;

      lift.moveVelocity(velocity);

      prev_error = error;

      delay(20);

    }

  }


  lift.moveVelocity(0);
  delay(20);
}
