#include "robot-config.h"
#include "AutonFunctions.h"
#include "DriverControl.h"

using namespace pros;

void driverControl() {
    while (true) {
        // Read joystick values
        int leftY = master.get_analog(ANALOG_LEFT_Y);
        int rightY = master.get_analog(ANALOG_RIGHT_Y);
        
        // Optional: Apply a deadband
        if (abs(leftY) < 10) leftY = 0;  // Adjust deadband threshold as needed
        if (abs(rightY) < 10) rightY = 0; // Adjust deadband threshold as needed

        // Move wheels based on joystick input
        back_left_wheels.move(leftY);
        front_left_wheels.move(leftY);
        back_right_wheels.move(rightY);
        middle_right_wheels.move(rightY);
        middle_left_wheels.move(leftY);
        front_right_wheels.move(rightY);
        top_front_right_wheels.move(rightY);
        top_front_left_wheels.move(leftY);
        top_back_left_wheels.move(leftY);
        top_back_right_wheels.move(rightY);

        // Short delay for control loop frequency
        delay(20); // Adjust as needed
    }
}



