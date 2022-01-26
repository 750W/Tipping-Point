#include "config.h"
using namespace okapi;

void drive_funct(void*){
  while(true && !auton_state){
    chassis->getModel()->arcade(
      joystick.getAnalog(okapi::ControllerAnalog::leftY),
      joystick.getAnalog(okapi::ControllerAnalog::rightX)
    );
    delay(20);
  }
  delay(20);
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
    position = position * totalTime / ( 3 * 50 );
    return position;
}

void acceleration_tracker(void*) {
    int time = 50;
    acceleration.push_back(0.0);
    while (true && auton_state) {
        double prev_vel = acceleration.at(ind - 1);
        double z_accel = imu_z.getAcceleration();
        double x_accel = imu_x.getAcceleration();
        double accel = sqrt ( (z_accel * z_accel) + (x_accel * x_accel) );
        acceleration.push_back( prev_vel + (accel * time) );
        totalTime = totalTime + time;
        ind = ind + 1;
        delay(time);
    }
}
