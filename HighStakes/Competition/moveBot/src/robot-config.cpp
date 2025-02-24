#include "robot-config.h"

using namespace pros;

/* 
  * LOOK FROM BEHIND ROBOT TO UNDERSTAND PORTS
  * THIS MEANS THAT YOU MUST LOOK AT THE ROBOT WITH THE SCREEN FACING YOU
 */

// Constants
#define TOP_MIDDLE_LEFT_PORT 3 // done
#define BOTTOM_MIDDLE_LEFT_PORT 4 // done
#define BACK_LEFT_PORT 8 // done 
#define TOP_MIDDLE_RIGHT_PORT 5 // done
#define BOTTOM_MIDDLE_RIGHT_PORT 6 // done
#define BACK_RIGHT_PORT 7 // done
#define INTAKE_PORT 9 // done

#define CLAMP_PORT 'A' // done

#define RED MOTOR_GEARSET_36
#define GREEN MOTOR_GEARSET_18
#define BLUE MOTOR_GEARSET_6

// Motors and Sensors

// left side
Motor middle_left_red_gear(TOP_MIDDLE_LEFT_PORT, BLUE, false); // done 
Motor middle_left_green_gear(BOTTOM_MIDDLE_LEFT_PORT, BLUE, false); // done
Motor back_left_green_gear(BACK_LEFT_PORT, BLUE, false);

// right side
Motor middle_right_red_gear(TOP_MIDDLE_RIGHT_PORT, BLUE, true); // done
Motor middle_right_green_gear(BOTTOM_MIDDLE_RIGHT_PORT, BLUE, true); // done
Motor back_right_green_gear(BACK_RIGHT_PORT, BLUE, true); // done

Motor intake(INTAKE_PORT, BLUE, false); // done

ADIDigitalOut clamp (CLAMP_PORT);

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

