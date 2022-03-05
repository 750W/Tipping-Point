#include "main.h"

const int FRONT_LEFT_MOTOR = 7;
const int FRONT_RIGHT_MOTOR = 14;
const int BACK_LEFT_MOTOR = 13;
const int BACK_RIGHT_MOTOR = 2;

const int BACK_INTAKE_MOTOR = 18;

const int LEFT_LIFT_MOTOR = 6;
const int RIGHT_LIFT_MOTOR = 9;

const int RING_INTAKE_MOTOR = 10;
const std::uint8_t IMU_PORT = 4;

extern okapi::Motor drive_fL;
extern okapi::Motor drive_fR;
extern okapi::Motor drive_bL;
extern okapi::Motor drive_bR;

extern okapi::Motor front_intake;
extern okapi::Motor back_intake;

extern okapi::Motor liftL;
extern okapi::Motor liftR;
extern okapi::MotorGroup lift;
extern okapi::Motor ring_intake;

extern std::shared_ptr<okapi::OdomChassisController> chassis;
extern int i;

extern okapi::Controller joystick;

extern okapi::ControllerButton l1;
extern okapi::ControllerButton r1;

extern okapi::ControllerButton l2;
extern okapi::ControllerButton r2;

extern okapi::ControllerButton up;
extern okapi::ControllerButton down;
extern okapi::ControllerButton left;
extern okapi::ControllerButton right;

extern okapi::ControllerButton x;
extern okapi::ControllerButton a;
extern okapi::ControllerButton y;
extern okapi::ControllerButton b;

extern okapi::MotorGroup front_drive;

extern bool auton_state;

extern std::vector<double> rotation_values;
extern int ind;
extern int totalTime;
extern pros::Imu imu;

extern pros::Task imu_task;
extern pros::Task drive;

extern pros::ADIDigitalOut piston;
extern okapi::ADIEncoder shaft_encoder;
extern okapi::ADIButton back_bumperswitch;

void stop();
void drive_tarePos();

void move_dist(double spd, int time);
void move_dist_drive(double spdL, double spdR);

void drive_PID(int ticks);

void front_clamp();
void front_unclamp();

void back_up();
void back_down();

void back_auto_clamp();
void back_auto_unclamp();

void ring_reverse();
void ring_forward();
void ring_stop();

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

void prog_skills();
void both_win_points_left();
void both_neutral_goals_right();

void auton_selector();

void drive_funct(void*);

void extend_piston(int time);
void contract_piston(int time);
