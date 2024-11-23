
#include "robot-config.h"
#include "AutonFunctions.h"
#include "pros/motors.hpp"
#include "pros/misc.hpp"


// Initialize the PID constants
double kp = 0.5;  // Proportional constant
double ki = 0.0;  // Integral constant (set to 0 initially, typically less used for basic moves)
double kd = 0.1;  // Derivative constant

// Function to move the robot forward using PID control
void moveForwardPID(double targetDistance, int maxSpeed) {
    double currentDistance = 0;  // This will depend on how you measure distance (e.g., encoder counts)
    double previousError = 0;
    double integral = 0;

    // Adjust PID constants dynamically for short distances
    if (targetDistance < 10) { // For distances less than 10 inches
        kp *= 1.5; // Increase proportional gain
        maxSpeed = std::max(50, maxSpeed / 2); // Limit max speed
    }

    while (currentDistance < targetDistance) {
        double error = targetDistance - currentDistance;
        integral += error;
        double derivative = error - previousError;

        // Compute PID control value
        int controlSignal = kp * error + ki * integral + kd * derivative;

        // Apply control signal to motors, limiting to maxSpeed
        double leftSpeed = std::min(maxSpeed, std::max(-maxSpeed, controlSignal));
        double rightSpeed = std::min(maxSpeed, std::max(-maxSpeed, controlSignal));


        leftSpeed = -leftSpeed;
        rightSpeed = -rightSpeed;
        
        // Apply motor speeds (replace with your motor control functions)
            // left side
            middle_left_red_gear.move_velocity(leftSpeed);
            middle_left_green_gear.move_velocity(leftSpeed);
            back_left_green_gear.move_velocity(leftSpeed);

            // right side
            middle_right_red_gear.move_velocity(rightSpeed);
            middle_right_green_gear.move_velocity(rightSpeed);
            back_right_green_gear.move_velocity(rightSpeed);

        previousError = error;


        // Update current distance based on encoders (this is a placeholder)
        currentDistance = degreesToInches(-middle_left_green_gear.get_position());  // Example: use encoder position to track distance

        delay(10);  // Adjust loop frequency as needed
    }

    // left side
    middle_left_red_gear.move_velocity(0);
    middle_left_green_gear.move_velocity(0);
    back_left_green_gear.move_velocity(0);

    // right side
    middle_right_red_gear.move_velocity(0);
    middle_right_green_gear.move_velocity(0);
    back_right_green_gear.move_velocity(0);

    return;
}

// Function to turn the robot clockwise for a fixed amount of time
void turnClockwiseTime(int turnTime, int maxSpeed) {
    // Move the robot in opposite directions to turn
        // left side
        middle_left_red_gear.move_velocity(-maxSpeed);
        middle_left_green_gear.move_velocity(-maxSpeed);
        back_left_green_gear.move_velocity(-maxSpeed);

        // right side
        middle_right_red_gear.move_velocity(maxSpeed);
        middle_right_green_gear.move_velocity(maxSpeed);
        back_right_green_gear.move_velocity(maxSpeed);

    delay(turnTime);  // Run the motors for the specified time

    // Stop motors after the turn
        // left side
        middle_left_red_gear.move_velocity(0);
        middle_left_green_gear.move_velocity(0);
        back_left_green_gear.move_velocity(0);

        // right side
        middle_right_red_gear.move_velocity(0);
        middle_right_green_gear.move_velocity(0);
        back_right_green_gear.move_velocity(0);
    return;
}

// convert from degrees to inches
double degreesToInches(double degrees) {
    double radius = 1.375; // radius of wheel in inches
    double pi = 3.1415926535897;

    return (degrees * pi * radius) / 180;
}
