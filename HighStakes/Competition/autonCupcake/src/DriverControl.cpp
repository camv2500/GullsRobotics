#include "robot-config.h"
#include "AutonFunctions.h"
#include "DriverControl.h"


using namespace pros;

void driverControl() {
    // while (true) {
    //     // Read joystick values
    //     int leftY = master.get_analog(ANALOG_LEFT_Y);
    //     int rightY = master.get_analog(ANALOG_RIGHT_Y);
        
    //     // Optional: Apply a deadband
    //     if (abs(leftY) < 10) leftY = 0;  // Adjust deadband threshold as needed
    //     if (abs(rightY) < 10) rightY = 0; // Adjust deadband threshold as needed

    //     // Move wheels based on joystick input
    //     back_left_wheels.move(leftY);
    //     front_left_wheels.move(leftY);
    //     back_right_wheels.move(rightY);
    //     middle_right_wheels.move(rightY);
    //     middle_left_wheels.move(leftY);
    //     front_right_wheels.move(rightY);
    //     top_front_right_wheels.move(rightY);
    //     top_front_left_wheels.move(leftY);
    //     top_back_left_wheels.move(leftY);
    //     top_back_right_wheels.move(rightY);

    //     // Short delay for control loop frequency
    //     delay(20); // Adjust as needed
    // }
    while (true) {
        // Read joystick values
        int leftY = -1*master.get_analog(ANALOG_LEFT_Y);
        int rightX = -1*master.get_analog(ANALOG_RIGHT_X);
        
        // Optional: Apply a deadband
        if (abs(leftY) < 10) leftY = 0;  // Adjust deadband threshold as needed
        if (abs(rightX) < 10) rightX = 0; // Adjust deadband threshold as needed
        
        // int power = leftY * 127 / 100;
        // int turn = rightX * 127 / 100;

        // int left_power = power + turn;   // Left motor receives more power when turning right
        // int right_power = power - turn;  // Right motor receives more power when turning left

        // Scale joystick values for extra speed (2x boost), but limit to the range -127 to 127
        // int left_power = ((leftY + rightX) * 2) * 0.95;   // Left motor control
        // int right_power = ((leftY - rightX) * 2) * 1.05;  // Right motor control
        int left_power = (leftY + rightX) * 2;   // Left motor control
        int right_power = (leftY - rightX) * 2;  // Right motor control


        if (rightX >= 0) {  // Moving forward
            left_power = left_power * 0.95;
            right_power = right_power * 1.05;
        } else {  // Moving backward
            left_power = left_power * 0.95;
            right_power = right_power * 1.05;
        }

        // Ensure the values don't exceed the maximum allowed motor power
        left_power = std::max(-127, std::min(127, left_power));
        right_power = std::max(-127, std::min(127, right_power));

        // Move wheels based on joystick input
        middle_left_red_gear.move(left_power);
        middle_left_green_gear.move(left_power);
        back_left_green_gear.move(left_power);

        // right side
        middle_right_red_gear.move(right_power);
        middle_right_green_gear.move(right_power);
        back_right_green_gear.move(right_power);

        // Short delay for control loop frequency
        delay(20); // Adjust as needed
    }
}



