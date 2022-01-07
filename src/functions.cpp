#include "main.h"
#include "config.h"

void move_dist (float spd, int time) {

  drive_fL.moveVelocity(spd);
  drive_fR.moveVelocity(spd);
  drive_bL.moveVelocity(spd);
  drive_bR.moveVelocity(spd);
  delay(time);

}

double getCurrentPosition(){
    double position = 0;
    position = position + acceleration.at(0);
    for(std::vector<double>::size_type i = 1; i != acceleration.size() - 1; i++)  {
        if(i % 2 == 1){
            position = position + ( 2 * acceleration.at(i) );
        }
        else {
            position = position + ( 4 * acceleration.at(i) );
        }
    }
    position = position + acceleration.at(acceleration.size());
    position = position * totalTime / ( 3 * 5 );
    return position;
}

pros::Task acceleration_tracker(void*){
    int time = 5;
    acceleration.push_back(0.0);
    while(auton_state == false){
        while(auton_state == true){
            double prev_vel = acceleration.at(ind - 1);
            double z_accel = imu_z.getAcceleration();
            double x_accel = imu_x.getAcceleration();
            double accel = sqrt ( (z_accel * z_accel) + (x_accel * x_accel) );
            acceleration.push_back( prev_vel + (accel * time) );
            totalTime = totalTime + time;
            ind = ind + 1;
            delay(time);
        }
        delay(time);
    }
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

  lift.moveVelocity(100);

}

void lift_down () {

  lift.moveVelocity(-100);

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

      printf ("Error: %f, %f\n", errorL, errorR) ;
      printf ("velocity: %f, %f\n", velocityL, velocityR) ;

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

  double errorL, errorR, kP, velocityL, velocityR;
  double total_errorL, total_errorR, kI;
  double prev_errorL, prev_errorR, kD, derivativeL, derivativeR;
  int l_begpos, r_begpos, lpos, rpos, desired_val;

  r_begpos = (int)drive_fR.getPosition();
  l_begpos = (int)drive_fL.getPosition();

  if ( l_begpos != (int)dist && r_begpos != (int)dist ) {

    kP = 0.1;
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

      //printf ("Error: %f, %f", errorL, errorR) ;
      //printf ("velocity: %f, %f", velocityL, velocityR) ;

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

void drive_tarePos() {

  drive_fR.tarePosition();
  drive_bR.tarePosition();
  drive_fL.tarePosition();
  drive_bL.tarePosition();

}

void turn_PID(double dist){

    double errorL, errorR, kP, velocityL, velocityR;
    double total_errorL, total_errorR, kI;
    double prev_errorL, prev_errorR, kD, derivativeL, derivativeR;
    int l_begpos, r_begpos, lpos, rpos, desired_val;

    r_begpos = (int)drive_fR.getPosition();
    l_begpos = (int)drive_fL.getPosition();

    if ( l_begpos != (int)dist && r_begpos != (int)dist ) {

      kP = 0.1;
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

        //printf ("Error: %f, %f", errorL, errorR) ;
        //printf ("velocity: %f, %f", velocityL, velocityR) ;

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
