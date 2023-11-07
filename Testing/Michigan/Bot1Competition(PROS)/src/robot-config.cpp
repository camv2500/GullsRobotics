#include "robot-config.h"

// Red is 36:1 (100 rpm), Green is 18:1 (200 rpm), Blue is 6:1 (600 rpm).

// Constants
// #define LEFT_WHEELS_PORT 1
// #define RIGHT_WHEELS_PORT 10

Motor lMotor1 (6, E_MOTOR_GEARSET_06, true);
Motor lMotor2 (11, E_MOTOR_GEARSET_06, true);
Motor lMotor3 (13, E_MOTOR_GEARSET_06, true);
Motor lMotor4 (12, E_MOTOR_GEARSET_06, true);
Motor rMotor1 (8, E_MOTOR_GEARSET_06, false);
Motor rMotor2 (9, E_MOTOR_GEARSET_06, false);
Motor rMotor3 (10, E_MOTOR_GEARSET_06, false);
Motor rMotor4 (2, E_MOTOR_GEARSET_06, false);
Motor cataMotor (1, E_MOTOR_GEARSET_36, false);
Motor intakeRollerMotor (19, E_MOTOR_GEARSET_06, false);
Controller master (CONTROLLER_MASTER);
// limit cataLimit = limit(Brain.ThreeWirePort.C);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

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
	master.clear();

	lcd::register_btn1_cb(on_center_button);
}

