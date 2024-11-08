
#include "robot-config.h"
#include "AutonFunctions.h"
#include "pros/motors.hpp"
#include "pros/misc.hpp"


// Initialize the PID constants
double kp = 0.5;  // Proportional constant
double ki = 0.0;  // Integral constant (set to 0 initially, typically less used for basic moves)
double kd = 0.1;  // Derivative constant

// Function to move the robot forward using PID control
void moveForwardPID(int targetDistance, int maxSpeed, int moveTime) {
    int currentDistance = 0;  // This will depend on how you measure distance (e.g., encoder counts)
    int previousError = 0;
    int integral = 0;

    while (currentDistance < targetDistance) {
        int error = targetDistance - currentDistance;
        integral += error;
        int derivative = error - previousError;

        // Compute PID control value
        int controlSignal = kp * error + ki * integral + kd * derivative;

        // Apply control signal to motors, limiting to maxSpeed
        int leftSpeed = std::max(-maxSpeed, std::min(maxSpeed, controlSignal));
        int rightSpeed = std::max(-maxSpeed, std::min(maxSpeed, controlSignal));

        // Apply motor speeds (replace with your motor control functions)
        front_left_wheels.move_velocity(-leftSpeed);
        middle_left_wheels.move_velocity(-leftSpeed);
        back_left_wheels.move_velocity(-leftSpeed);
        top_front_left_wheels.move_velocity(-leftSpeed);
        top_back_left_wheels.move_velocity(-leftSpeed);

        front_right_wheels.move_velocity(-rightSpeed);
        middle_right_wheels.move_velocity(-rightSpeed);
        back_right_wheels.move_velocity(-rightSpeed);
        top_front_right_wheels.move_velocity(-rightSpeed);
        top_back_right_wheels.move_velocity(-rightSpeed);

        previousError = error;

        // Update current distance based on encoders (this is a placeholder)
        currentDistance = front_left_wheels.get_position();  // Example: use encoder position to track distance

        delay(moveTime);  // Adjust loop frequency as needed
    }

    // Stop motors once the target distance is reached
    front_left_wheels.move_velocity(0);
    middle_left_wheels.move_velocity(0);
    back_left_wheels.move_velocity(0);
    top_front_left_wheels.move_velocity(0);
    top_back_left_wheels.move_velocity(0);

    front_right_wheels.move_velocity(0);
    middle_right_wheels.move_velocity(0);
    back_right_wheels.move_velocity(0);
    top_front_right_wheels.move_velocity(0);
    top_back_right_wheels.move_velocity(0);
}

// Function to turn the robot clockwise for a fixed amount of time
void turnClockwiseTime(int turnTime, int maxSpeed) {
    // Move the robot in opposite directions to turn
    front_left_wheels.move_velocity(-maxSpeed);
    middle_left_wheels.move_velocity(-maxSpeed);
    back_left_wheels.move_velocity(-maxSpeed);
    top_front_left_wheels.move_velocity(-maxSpeed);
    top_back_left_wheels.move_velocity(-maxSpeed);

    front_right_wheels.move_velocity(maxSpeed);  // Reverse right motors for clockwise turn
    middle_right_wheels.move_velocity(maxSpeed);
    back_right_wheels.move_velocity(maxSpeed);
    top_front_right_wheels.move_velocity(maxSpeed);
    top_back_right_wheels.move_velocity(maxSpeed);

    delay(turnTime);  // Run the motors for the specified time

    // Stop motors after the turn
    front_left_wheels.move_velocity(0);
    middle_left_wheels.move_velocity(0);
    back_left_wheels.move_velocity(0);
    top_front_left_wheels.move_velocity(0);
    top_back_left_wheels.move_velocity(0);

    front_right_wheels.move_velocity(0);
    middle_right_wheels.move_velocity(0);
    back_right_wheels.move_velocity(0);
    top_front_right_wheels.move_velocity(0);
    top_back_right_wheels.move_velocity(0);
}
