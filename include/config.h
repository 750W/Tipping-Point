#define CONFIG_H
#include "main.h"

const int FRONT_LEFT_MOTOR = 7;
const int FRONT_RIGHT_MOTOR = 14;
const int BACK_LEFT_MOTOR = 13;
const int BACK_RIGHT_MOTOR = 2;

const int FRONT_INTAKE_MOTOR = 5;
const int BACK_INTAKE_MOTOR = 18;

const int LIFT_MOTOR = 9;

extern okapi::Motor drive_fL;
extern okapi::Motor drive_fR;
extern okapi::Motor drive_bL;
extern okapi::Motor drive_bR;

extern okapi::Motor front_intake;
extern okapi::Motor back_intake;

extern okapi::Motor lift;

extern std::shared_ptr<okapi::OdomChassisController> chassis;
extern int i;

extern okapi::Controller joystick;

extern okapi::ControllerButton frontTakeIn;
extern okapi::ControllerButton frontTakeOut;

extern okapi::ControllerButton backTakeIn;
extern okapi::ControllerButton backTakeOut;

extern okapi::ControllerButton up;
extern okapi::ControllerButton down;
extern okapi::ControllerButton left;
extern okapi::ControllerButton right;

extern okapi::ControllerButton x;
extern okapi::ControllerButton a;
extern okapi::ControllerButton y;
extern okapi::ControllerButton b;

extern okapi::MotorGroup front_drive;

extern okapi::ADIButton back_bumperswitch;

extern bool auton_state;

extern std::vector<double> acceleration;
extern int ind;
extern int totalTime;
extern okapi::IMU imu_x;
extern okapi::IMU imu_z;

extern pros::Task acceleration_tracker_task;
extern pros::Task drive;

extern pros::ADIDigitalOut piston;

void stop();
void drive_tarePos();

void move_dist(double spd, int time);
void move_dist_drive(double spdL, double spdR);

void drive_PID(double dist);

void front_clamp();
void front_unclamp();

void back_clamp();
void back_unclamp();

void back_auto_clamp();
void back_auto_unclamp();

void lift_up();
void lift_down();

void lift_PID(int deg);

void turn_cw(float spd, int time);
void turn_ccw(float spd, int time);

void turn_cw_PID(int deg);
void turn_ccw_PID(int deg);

void turn_PID(int deg);

void mbl_goal();
void left_win_point();
void right_win_point();
void new_auton_trial();
void right_win_point_mbl_goal();

void auton_selector();

void drive_funct(void*);
void acceleration_tracker(void*);
double getCurrentPosition();

void extend_piston(int time);
void contract_piston(int time);