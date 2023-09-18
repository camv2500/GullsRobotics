#include "main.h"

pros::Controller Controller1(pros::E_CONTROLLER_MASTER);
pros::Motor lmotor1 (2, pros::E_MOTOR_GEAR_BLUE, true, pros:: E_MOTOR_ENCODER_DEGREES);
pros::Motor lmotor2 (11, pros::E_MOTOR_GEAR_BLUE, true, pros:: E_MOTOR_ENCODER_DEGREES);
pros::Motor rmotor1 (5, pros::E_MOTOR_GEAR_BLUE, false, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor rmotor2 (19, pros::E_MOTOR_GEAR_BLUE, false, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor_Group leftMotorGroup ({lmotor1, lmotor2});
pros::Motor_Group rightMotorGroup ({rmotor1, rmotor2});

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(1, "Hello PROS User!");

	pros::lcd::register_btn1_cb(on_center_button);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */

 double controlCurve(double conP){
  //Slow curve
  return (exp(-14.6/10)+exp((fabs(conP)-100)/10)*(1-exp(-14.6/10)))*conP;
}

void opcontrol() {
	while (true) {
		double leftDrive = (Controller1.get_analog(ANALOG_RIGHT_Y) - Controller1.get_analog(ANALOG_RIGHT_X));
    	double rightDrive = (Controller1.get_analog(ANALOG_RIGHT_Y) + Controller1.get_analog(ANALOG_RIGHT_X));
		leftMotorGroup.move(controlCurve(leftDrive));
		rightMotorGroup.move(controlCurve(rightDrive));

		pros::delay(10);
	}
}