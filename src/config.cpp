#include "main.h"
#include "config.h"
using namespace okapi;
//Hello Anirudh welcome to the git!
//Hi friends
okapi::Motor drive_fL(FRONT_LEFT_MOTOR, false, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees);
okapi::Motor drive_fR(FRONT_RIGHT_MOTOR, true, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees);
okapi::Motor drive_bL(BACK_LEFT_MOTOR, false, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees);
okapi::Motor drive_bR(BACK_RIGHT_MOTOR, true, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees);
okapi::Motor front_intake(FRONT_INTAKE_MOTOR, true, AbstractMotor::gearset::red, AbstractMotor::encoderUnits::degrees);
okapi::Motor back_intake(BACK_INTAKE_MOTOR, false, AbstractMotor::gearset::red, AbstractMotor::encoderUnits::degrees);
okapi::Motor liftL(LEFT_LIFT_MOTOR, false, AbstractMotor::gearset::red, AbstractMotor::encoderUnits::degrees);
okapi::Motor liftR(RIGHT_LIFT_MOTOR, true, AbstractMotor::gearset::red, AbstractMotor::encoderUnits::degrees);

std::shared_ptr<okapi::ChassisController> chassis = ChassisControllerBuilder()
    .withMotors(
        {drive_fL, drive_bL},
        {drive_fR, drive_bR}
    ).withDimensions(
        AbstractMotor::gearset::green,
        {
            {4.0_in, 12.0_in},
            static_cast<int32_t>(imev5GreenTPR)
        }
    ).withMaxVelocity(150
    ).withOdometry(
    ).buildOdometry();

okapi::MotorGroup lift({liftL, liftR});

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

int i = 0;
bool auton_state = false;
std::vector<double> acceleration;
int ind = 1;
int totalTime;