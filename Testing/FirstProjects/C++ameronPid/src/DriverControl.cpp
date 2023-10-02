#include "robot-config.h"
#include "AutonFunctions.h"
#include "DriverControl.h"

using namespace pros;

// Constants

const int Intake_Speed = 100; // Percentage intake motor speed
const int Lift_Speed = 100; // Percentage Lift motor speed

// Variables

int BrakeButton; // Variable defined for brake button

// Variables defined for intake direction
int Intake_in;  // Takes in the discs
int Intake_out; // Releases discs

// Boolean logic for double tap intake ability
bool continuous_in = false;
bool continuous_out = false;

bool lift_press_up = false;
bool lift_press_down = false;

// Functions

// Function for intake double tap, keeps track of interval between presses, called as interupt
int lastPressIN = 0;
int timeThresholdIN = 250;
void ContinuousIntakeDoubleTap() {

  int time = millis(); 
  int interval = time - lastPressIN;
  if (interval < timeThresholdIN) {

    continuous_in = !continuous_in;

  }

  lastPressIN = time;
  delay(20);

}

// Function for outtake double tap, keeps track of interval between presses, called as interupt
int lastPressOUT = 0;
int timeThresholdOUT = 250; 
void ContinuousOuttakeDoubleTap() {

  int time = millis();
  int interval = time - lastPressOUT;
  if (interval < timeThresholdOUT) {

    continuous_out = !continuous_out;

  } 

  lastPressOUT = time;
  delay(20);

}

void control() {

    while (true) {
        
        BrakeButton = Controller1.get_digital(E_CONTROLLER_DIGITAL_B);

        delay(10);
    }
}

void driver() {

    while (true) {

        if (!BrakeButton) {
            
            double leftDrive = (Controller1.get_analog(ANALOG_RIGHT_Y) + Controller1.get_analog(ANALOG_RIGHT_X));
            double rightDrive = (Controller1.get_analog(ANALOG_RIGHT_Y) - Controller1.get_analog(ANALOG_RIGHT_X));
            leftMotorGroup.move(leftDrive);
            rightMotorGroup.move(rightDrive);
            lcd::print(1, "%f", lmotor1.get_position());

        }

		delay(10);
	}

}