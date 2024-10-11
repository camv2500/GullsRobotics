#include "robot-config.h"

using namespace pros;

// Constants
#define LEFT_WHEELS_PORT 1
#define RIGHT_WHEELS_PORT 10

// Motors and Sensors
Motor left_wheels (LEFT_WHEELS_PORT);
Motor right_wheels (RIGHT_WHEELS_PORT, true); // This reverses the motor
Controller master (CONTROLLER_MASTER);

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

