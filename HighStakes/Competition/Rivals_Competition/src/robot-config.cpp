#include "robot-config.h"

using namespace pros;

/* 
  * LOOK FROM BEHIND ROBOT TO UNDERSTAND PORTS
  * THIS MEANS THAT YOU MUST LOOK AT THE ROBOT WITH THE SCREEN FACING YOU
 */

// Constants
#define FRONT_LEFT_PORT 8 // done
#define BACK_LEFT_PORT 6 // done 
#define FRONT_RIGHT_PORT 4 // done
#define BACK_RIGHT_PORT 21 // done
#define FLIPPER_PORT 7 // done
#define INTAKE_PORT 9 // done
#define INERTIAL_SENSOR_PORT 10 // done
#define ROTATION_PORT 3 // done

#define CLAMP_PORT 'A' // done

Imu inertial_sensor(INERTIAL_SENSOR_PORT); // Inertial Sensor

#define RED MOTOR_GEARSET_36
#define GREEN MOTOR_GEARSET_18
#define BLUE MOTOR_GEARSET_6

// Motors and Sensors

// left side
Motor front_left_wheels(FRONT_LEFT_PORT, BLUE, true); // done
Motor back_left_wheels(BACK_LEFT_PORT, BLUE, true);

// right side
Motor front_right_wheels(FRONT_RIGHT_PORT, BLUE, false); // done
Motor back_right_wheels(BACK_RIGHT_PORT, BLUE, false); // done

Motor intake(INTAKE_PORT, BLUE, false); // done

Motor flipper(FLIPPER_PORT, RED, false); // done

Rotation rotation(ROTATION_PORT); // done

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

