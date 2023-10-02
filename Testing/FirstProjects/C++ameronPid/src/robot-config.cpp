#include "robot-config.h"

using namespace pros;

// Red is 36:1 (100 rpm), Green is 18:1 (200 rpm), Blue is 6:1 (600 rpm).

// Constants
#define LEFT_WHEELS_PORT 1
#define RIGHT_WHEELS_PORT 10

// Motors and Sensors
Controller Controller1(E_CONTROLLER_MASTER);
Motor lmotor1 (2, E_MOTOR_GEAR_BLUE, true,  E_MOTOR_ENCODER_DEGREES);
Motor lmotor2 (11, E_MOTOR_GEAR_BLUE, true,  E_MOTOR_ENCODER_DEGREES);
Motor rmotor1 (5, E_MOTOR_GEAR_BLUE, false, E_MOTOR_ENCODER_DEGREES);
Motor rmotor2 (19, E_MOTOR_GEAR_BLUE, false, E_MOTOR_ENCODER_DEGREES);
Motor_Group leftMotorGroup ({lmotor1, lmotor2});
Motor_Group rightMotorGroup ({rmotor1, rmotor2});

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
		lcd::set_text(2, "I was pressed!");
	} else {
		lcd::clear_line(2);
	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	lcd::initialize();
	lcd::set_text(1, "Hello PROS User!");

	lcd::register_btn1_cb(on_center_button);
}

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

