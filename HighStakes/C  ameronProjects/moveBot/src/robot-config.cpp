#include "robot-config.h"

using namespace pros;

// Constants
#define FRONT_LEFT_PORT 11
#define BACK_LEFT_PORT 13
#define BACK_RIGHT_PORT 14
#define FRONT_RIGHT_PORT 19
#define MIDDLE_RIGHT_PORT 18
#define MIDDLE_LEFT_PORT 15
#define TOP_FRONT_RIGHT_PORT 20
#define TOP_BACK_LEFT_PORT 12
#define TOP_FRONT_LEFT_PORT 2
#define TOP_BACK_RIGHT_PORT 16

#define RED MOTOR_GEARSET_36
#define GREEN MOTOR_GEARSET_18
#define BLUE MOTOR_GEARSET_6

// Motors and Sensors
Motor front_left_wheels (FRONT_LEFT_PORT, BLUE, false); // 
Motor middle_left_wheels (MIDDLE_LEFT_PORT, BLUE, false); // 
Motor back_left_wheels (BACK_LEFT_PORT, BLUE, true); // 
Motor top_front_left_wheels (TOP_FRONT_LEFT_PORT, BLUE, true); // 
Motor top_back_left_wheels (TOP_BACK_LEFT_PORT, BLUE, true); // 

Motor front_right_wheels (FRONT_RIGHT_PORT, BLUE, true); // 
Motor middle_right_wheels (MIDDLE_RIGHT_PORT, BLUE, true); // 
Motor back_right_wheels (BACK_RIGHT_PORT, BLUE, false); // 
Motor top_front_right_wheels (TOP_FRONT_RIGHT_PORT, BLUE, false); // 
Motor top_back_right_wheels (TOP_BACK_RIGHT_PORT, BLUE, false); // 

// Motor_Group left (back_left_wheels, middle_left_wheels, front_left_wheels, top_front_left_wheels, top_back_left_wheels)

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

