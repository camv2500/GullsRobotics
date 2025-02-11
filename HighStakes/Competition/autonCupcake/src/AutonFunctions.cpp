#include "robot-config.h"
#include "AutonFunctions.h"
#include "DriverControl.h"
#include "pros/motors.hpp"
#include "pros/misc.hpp"

// NOTE: The robot now moves and stops at the correct position.
// HOWEVER: The while loop does not break and continues to move a very small distance
// THE ERROR IS PROBABLY ON LINES 88 or 112

/////////////////////////////////////////////////////////////////////////////////////
//////                              GLOBAL CONSTANTS                           //////
/////////////////////////////////////////////////////////////////////////////////////

// Initialize the PID constants
double kp = 0.9;  // Proportional constant (tuned for inches)
double ki = 0.0;  // Integral constant (set to 0 initially, typically less used for basic moves)
double kd = 0.2; // Derivative constant (adjusted)

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

// Function to reset the motor encoders
void resetEncoders() {
    front_left_wheels.tare_position();
    middle_left_wheels.tare_position();
    back_left_wheels.tare_position();
    top_front_left_wheels.tare_position();
    top_back_left_wheels.tare_position();

    front_right_wheels.tare_position();
    middle_right_wheels.tare_position();
    back_right_wheels.tare_position();
    top_front_right_wheels.tare_position();
    top_back_right_wheels.tare_position();
}

// // Function to get the average encoder value of the X-Drive
// double getAverageEncoderValue(bool ab = false) {
//     if (ab) {
//       return (fabs(FrontL.get_position()) + fabs(RearL.get_position()) + fabs(FrontR.get_position()) + fabs(RearR.get_position())) / 4.0;
//     }
//     else {
//       return (FrontL.get_position() + RearL.get_position() + FrontR.get_position() + RearR.get_position()) / 4.0;
//     }
//   }

// Function to move the robot forward using PID control
void moveForwardPID(double targetDistance, int maxSpeed) {
    double currentDistance = 0; 
    double previousError = 0;
    double integral = 0;
    double integralMax = 100; // Maximum value for integral term

    resetEncoders();

    // Adjust PID constants dynamically for short distances
    if (targetDistance < 10) { // For distances less than 10 inches
        kp *= 1.5; // Increase proportional gain
        maxSpeed = std::max(50, maxSpeed / 2); // Limit max speed
    }

    while (true) {
        // Update current distance
        currentDistance = -degreesToInches(middle_right_wheels.get_position());
        

        double error = targetDistance - currentDistance;

        // Debug prints
        printf("Current Distance: %f inches\n", currentDistance);
        printf("Error: %f inches\n", error);
        
        //the error lies here
        if (fabs(error) < 1.0) {
            break;
        }

        // integral = std::max(-integralMax, std::min(integral, integralMax));
        integral += error;
        if (integral > integralMax) { // Anti-windup
            integral = integralMax;
        } else if (integral < -integralMax) {
            integral = -integralMax;
        }
        double derivative = error - previousError;

        // Compute PID control value
        int controlSignal = kp * error + ki * integral + kd * derivative;

        // Apply control signal to motors, limiting to maxSpeed
        double leftSpeed = std::min(maxSpeed, std::max(-maxSpeed, controlSignal));
        double rightSpeed = std::min(maxSpeed, std::max(-maxSpeed, controlSignal));

        leftSpeed = -leftSpeed;
        rightSpeed = -rightSpeed;

        //the error lies here
        if (fabs(error) < 3.0) {
            leftSpeed *= 0.5;
            rightSpeed *= 0.5;
        }


        // left side 
        front_left_wheels.move(leftSpeed);
        middle_left_wheels.move(leftSpeed);
        back_left_wheels.move(leftSpeed);
        top_front_left_wheels.move(leftSpeed);
        top_back_left_wheels.move(leftSpeed);

        // right side
        front_right_wheels.move(rightSpeed);
        middle_right_wheels.move(rightSpeed);
        back_right_wheels.move(rightSpeed);
        top_front_right_wheels.move(rightSpeed);
        top_back_right_wheels.move(rightSpeed);

        previousError = error;

        // currentDistance = middle_left_wheels.get_position() / 360.0;

        delay(0.5); 
    }

    // Stop motors
    // left side
    front_left_wheels.move(-10);
    middle_left_wheels.move(-10);
    back_left_wheels.move(-10);
    top_front_left_wheels.move(-10);
    top_back_left_wheels.move(-10);

    // right side
    front_right_wheels.move(-10);
    middle_right_wheels.move(-10);
    back_right_wheels.move(-10);
    top_front_right_wheels.move(-10);
    top_back_right_wheels.move(-10);

    return;
}

// Function to turn the robot clockwise for a fixed amount of time
void turnClockwiseTime(int turnTime, int maxSpeed) {
    // Move the robot in opposite directions to turn
    // left side
    front_left_wheels.move(-maxSpeed);
    middle_left_wheels.move(-maxSpeed);
    back_left_wheels.move(-maxSpeed);
    top_front_left_wheels.move(-maxSpeed);
    top_back_left_wheels.move(-maxSpeed);

    // right side
    front_right_wheels.move(maxSpeed);
    middle_right_wheels.move(maxSpeed);
    back_right_wheels.move(maxSpeed);
    top_front_right_wheels.move(maxSpeed);
    top_back_right_wheels.move(maxSpeed);

    delay(turnTime);  // Run the motors for the specified time

    // Stop motors after the turn
    // left side
    front_left_wheels.move(0);
    middle_left_wheels.move(0);
    back_left_wheels.move(0);
    top_front_left_wheels.move(0);
    top_back_left_wheels.move(0);

    // right side
    front_right_wheels.move(0);
    middle_right_wheels.move(0);
    back_right_wheels.move(0);
    top_front_right_wheels.move(0);
    top_back_right_wheels.move(0);

    return;
}

// Convert from degrees to inches
double degreesToInches(double degrees) {
    double pi = 3.1415926535897;
    double wheelCircumference = wheelDiameter * pi;

    return (degrees / 360) * wheelCircumference;
}