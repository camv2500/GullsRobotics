#include "robot-config.h"
#include "AutonFunctions.h"
#include "DriverControl.h"
#include "pros/motors.hpp"
#include "pros/misc.hpp"

/////////////////////////////////////////////////////////////////////////////////////
//////                              GLOBAL CONSTANTS                           //////
/////////////////////////////////////////////////////////////////////////////////////

// Initialize the PID constants
double kp = 0.4;  // Proportional constant (tuned for inches)
double ki = 0.0;  // Integral constant (set to 0 initially, typically less used for basic moves)
double kd = 0.05; // Derivative constant (adjusted)

double wheelDiameter = 2.75; // Wheel diameter in inches

/////////////////////////////////////////////////////////////////////////////////////
//////                               GLOBAL VARIABLES                          //////
/////////////////////////////////////////////////////////////////////////////////////

// global variables

/////////////////////////////////////////////////////////////////////////////////////
//////                               OTHER VARIABLES                           //////
/////////////////////////////////////////////////////////////////////////////////////

// Other Variables

/////////////////////////////////////////////////////////////////////////////////////
//////                                 FUNCTIONS                               //////
/////////////////////////////////////////////////////////////////////////////////////

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
        front_left_wheels.move_velocity(leftSpeed);
        middle_left_wheels.move_velocity(leftSpeed);
        back_left_wheels.move_velocity(leftSpeed);
        top_front_left_wheels.move_velocity(leftSpeed);
        top_back_left_wheels.move_velocity(leftSpeed);

        // right side
        front_right_wheels.move_velocity(rightSpeed);
        middle_right_wheels.move_velocity(rightSpeed);
        back_right_wheels.move_velocity(rightSpeed);
        top_front_right_wheels.move_velocity(rightSpeed);
        top_back_right_wheels.move_velocity(rightSpeed);

        previousError = error;

        // Update current distance based on encoders (this is a placeholder)
        currentDistance = degreesToInches(middle_left_wheels.get_position());  // Example: use encoder position to track distance

        delay(5);  // Adjust loop frequency as needed
    }

    // Stop motors
    // left side
    front_left_wheels.move_velocity(0);
    middle_left_wheels.move_velocity(0);
    back_left_wheels.move_velocity(0);
    top_front_left_wheels.move_velocity(0);
    top_back_left_wheels.move_velocity(0);

    // right side
    front_right_wheels.move_velocity(0);
    middle_right_wheels.move_velocity(0);
    back_right_wheels.move_velocity(0);
    top_front_right_wheels.move_velocity(0);
    top_back_right_wheels.move_velocity(0);

    return;
}

// Function to turn the robot clockwise for a fixed amount of time
void turnClockwiseTime(int turnTime, int maxSpeed) {
    // Move the robot in opposite directions to turn
    // left side
    front_left_wheels.move_velocity(-maxSpeed);
    middle_left_wheels.move_velocity(-maxSpeed);
    back_left_wheels.move_velocity(-maxSpeed);
    top_front_left_wheels.move_velocity(-maxSpeed);
    top_back_left_wheels.move_velocity(-maxSpeed);

    // right side
    front_right_wheels.move_velocity(maxSpeed);
    middle_right_wheels.move_velocity(maxSpeed);
    back_right_wheels.move_velocity(maxSpeed);
    top_front_right_wheels.move_velocity(maxSpeed);
    top_back_right_wheels.move_velocity(maxSpeed);

    delay(turnTime);  // Run the motors for the specified time

    // Stop motors after the turn
    // left side
    front_left_wheels.move_velocity(0);
    middle_left_wheels.move_velocity(0);
    back_left_wheels.move_velocity(0);
    top_front_left_wheels.move_velocity(0);
    top_back_left_wheels.move_velocity(0);

    // right side
    front_right_wheels.move_velocity(0);
    middle_right_wheels.move_velocity(0);
    back_right_wheels.move_velocity(0);
    top_front_right_wheels.move_velocity(0);
    top_back_right_wheels.move_velocity(0);

    return;
}

// Convert from degrees to inches
double degreesToInches(double degrees) {
    double pi = 3.1415926535897;
    double wheelCircumference = wheelDiameter * pi;

    return (degrees / 360) * wheelCircumference;
}