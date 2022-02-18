#include "config.h"
using namespace okapi;

okapi::Motor drive_fL(FRONT_LEFT_MOTOR, false, AbstractMotor::gearset::blue, AbstractMotor::encoderUnits::degrees);
okapi::Motor drive_fR(FRONT_RIGHT_MOTOR, true, AbstractMotor::gearset::blue, AbstractMotor::encoderUnits::degrees);
okapi::Motor drive_bL(BACK_LEFT_MOTOR, false, AbstractMotor::gearset::blue, AbstractMotor::encoderUnits::degrees);
okapi::Motor drive_bR(BACK_RIGHT_MOTOR, true, AbstractMotor::gearset::blue, AbstractMotor::encoderUnits::degrees);

okapi::Motor front_intake(FRONT_INTAKE_MOTOR, true, AbstractMotor::gearset::red, AbstractMotor::encoderUnits::degrees);
okapi::Motor back_intake(BACK_INTAKE_MOTOR, false, AbstractMotor::gearset::red, AbstractMotor::encoderUnits::degrees);

okapi::Motor lift(LIFT_MOTOR, false, AbstractMotor::gearset::red, AbstractMotor::encoderUnits::degrees);

std::shared_ptr<okapi::OdomChassisController> chassis = ChassisControllerBuilder()

    .withMotors(

        {drive_fL, drive_bL},
        {drive_fR, drive_bR}

    ).withDimensions(

        AbstractMotor::gearset::blue,
        {
            {4.0_in, 12.0_in},
            static_cast<int32_t>(imev5BlueTPR)
        }

    ).withMaxVelocity(480

    ).withOdometry(

    ).buildOdometry();

okapi::MotorGroup front_drive({drive_fL, drive_fR});

okapi::Controller joystick;

okapi::ControllerButton backTakeIn(ControllerDigital::L1);
okapi::ControllerButton backTakeOut(ControllerDigital::R1);

okapi::ControllerButton frontTakeIn(ControllerDigital::L2);
okapi::ControllerButton frontTakeOut(ControllerDigital::R2);

okapi::ControllerButton up(ControllerDigital::up);
okapi::ControllerButton down(ControllerDigital::down);
okapi::ControllerButton left(ControllerDigital::left);
okapi::ControllerButton right(ControllerDigital::right);

okapi::ControllerButton x(ControllerDigital::X);
okapi::ControllerButton a(ControllerDigital::A);
okapi::ControllerButton y(ControllerDigital::Y);
okapi::ControllerButton b(ControllerDigital::B);

okapi::ADIButton back_bumperswitch('H');

okapi::IMU imu_z(4,IMUAxes::z);//TODO:change port
okapi::IMU imu_x(4,IMUAxes::x);

pros::ADIDigitalOut piston('D');

int i = 0;
bool auton_state = true;
std::vector<double> acceleration;
int ind = 1;
int totalTime;
