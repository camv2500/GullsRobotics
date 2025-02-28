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
        int rightX = master.get_analog(ANALOG_RIGHT_X);
        
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
        front_left_wheels.move(left_power);
        back_left_wheels.move(left_power);

        // right side
        front_right_wheels.move(right_power);
        back_right_wheels.move(right_power);

        // Short delay for control loop frequency
        delay(20); // Adjust as needed
    }
}

void intakeRings() {
    while (true) {
        if (master.get_digital(DIGITAL_L1)) {
            // Move the intake motors forward
            master.print(0, 0, "Intaking Rings");
            intake.move(127);
        }
        else if (master.get_digital(DIGITAL_L2)) {
            // Move the intake motors forward
            master.print(0, 0, "Outaking Rings");
            intake.move(-127);
        }
        else {
            // Stop the intake motors
            // master.print(0, 0, "Stopping Intake");
            master.print(0, 0, "");
            intake.move(0);
        }
    }
}

// void outtakeRings() {
//     while (true) {
//         if (master.get_digital(DIGITAL_L2)) {
//             // Move the intake motors forward
//             master.print(0, 0, "Outaking Rings");
//         }
//     }
// }

void clampRings() {
    bool clampState = false;  // Track the clamp state manually
    // bool lastButtonState = false;  // Track the last state of the button
    while (true) {
        // Check if button is pressed and wasn't pressed before (edge detection)
        if (master.get_digital(DIGITAL_Y)) {
            // clampState = !clampState;  // Toggle the clamp state
            clamp.set_value(true); 
            master.print(0, 0, "Clamping Rings"); 
        }
        else if (master.get_digital(DIGITAL_X)) {
            clamp.set_value(false);
            master.print(0, 0, "Unclamping Rings");
        }
        // Display the new state
        // if (clampState) {
        //     master.print(0, 0, "Clamping Rings");
        // } else {
        //     master.print(0, 0, "Unclamping Rings");
        // }
        delay(20);
        // if (master.get_digital(DIGITAL_Y)) {
        //     if (clamp.get_value()) {
        //         // Move the intake motors forward
        //         master.print(0, 0, "Unclamping Rings");
        //         clamp.set_value(false);
        //     } else {
        //         // Move the intake motors forward
        //         master.print(0, 0, "Clamping Rings");
        //         clamp.set_value(true);
        //     }
            // // Move the intake motors forward
            // master.print(0, 0, "Clamping Rings");
            // clamp.set_value(true);
        // }
    }
}

void flipRings() {
    while (true) {
        if (master.get_digital(DIGITAL_R1)) {
            // Move the intake motors forward
            master.print(0, 0, "Flipping Rings");
            flipper.move(127);
        }
        else if (master.get_digital(DIGITAL_R2)) {
            // Move the intake motors forward
            master.print(0, 0, "Unflipping Rings");
            flipper.move(-127);
        }
        else {
            // Stop the intake motors
            // master.print(0, 0, "Stopping Intake");
            master.print(0, 0, "");
            flipper.move(0);
        }
    }
}
