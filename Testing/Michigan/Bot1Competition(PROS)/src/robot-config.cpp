#include "robot-config.h"

using namespace pros;

// Red is 36:1 (100 rpm), Green is 18:1 (200 rpm), Blue is 6:1 (600 rpm).

// Constants
#define LEFT_WHEELS_PORT 1
#define RIGHT_WHEELS_PORT 10

// Motors and Sensors
// Motor left_wheels (LEFT_WHEELS_PORT);
// Motor right_wheels (RIGHT_WHEELS_PORT, true); // This reverses the motor
Controller master (CONTROLLER_MASTER);
Motor FrontL (1, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES); // 11
Motor FrontR (10, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES); // 1
Motor RearL (11, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES); // 20
Motor RearR (20, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES); // 10

Rotation TrackL (2);
Rotation TrackR (9);

// Motor FrontL (9,  false);
// Motor FrontR (12, true);
// Motor RearL (10, false);
// Motor RearR (11, true);
// Motor RollerMotor (1, false);

// Motor intakeL (12, E_MOTOR_GEARSET_18, false);
// Motor intakeR (2, E_MOTOR_GEARSET_18, true);

// Motor liftL (13, E_MOTOR_GEARSET_36, true);
// Motor liftR (3, E_MOTOR_GEARSET_36, false);

Motor_Group leftDrive ({FrontL, RearR});
Motor_Group rightDrive ({FrontR, RearL});
Motor_Group leftRotate ({FrontL, RearL});
Motor_Group rightRotate ({FrontR, RearR});

// Motor_Group Intake ({intakeL, intakeR});

// Motor_Group Lift ({liftL, liftR});

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

