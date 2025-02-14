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
// double kp = 0.9;  // Proportional constant (tuned for inches)
// double ki = 0.0;  // Integral constant (set to 0 initially, typically less used for basic moves)
// double kd = 0.2; // Derivative constant (adjusted)

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

// Function to get the average encoder value
double getAverageEncoderValue(bool ab = false) {
    if (ab) {
      return (fabs(front_left_wheels.get_position()) + fabs(middle_left_wheels.get_position()) + fabs(back_left_wheels.get_position()) + fabs(top_front_left_wheels.get_position()) + fabs(top_back_left_wheels.get_position()) + fabs(front_right_wheels.get_position()) + fabs(middle_right_wheels.get_position()) + fabs(back_right_wheels.get_position()) + fabs(top_front_right_wheels.get_position()) + fabs(top_back_right_wheels.get_position())) / 10.0;
    }
    else {
      return (front_left_wheels.get_position() + middle_left_wheels.get_position() + back_left_wheels.get_position() + top_front_left_wheels.get_position() + top_back_left_wheels.get_position() + front_right_wheels.get_position() + middle_right_wheels.get_position() + back_right_wheels.get_position() + top_front_right_wheels.get_position() + top_back_right_wheels.get_position()) / 10.0;
    }
  }

// Function to move the robot forward using PID control
void moveForwardPID(double targetDistance, int maxSpeed) {
    // targetDistance = targetDistance / 1.25;
    double kp = 1.0;  // Proportional constant (tuned for inches) 1.0
    double ki = 0.01;  // Integral constant (set to 0 initially, typically less used for basic moves) 0.002
    double kd = 0.1; // Derivative constant (adjusted) 0.1
    double currentDistance = 0; 
    double previousError = 0;
    double integral = 0;
    double integralMax = 100; // Maximum value for integral term
    double local_kp = kp;
    double leftSpeed;
    double rightSpeed;

    resetEncoders();

    // Adjust PID constants dynamically for short distances
    if (targetDistance < 10) { // For distances less than 10 inches
        local_kp *= 1.5; // Increase proportional gain
        maxSpeed = std::max(50, maxSpeed / 2); // Limit max speed
    }

    while (fabs(currentDistance) < fabs(targetDistance) / 1.5) {
        lcd::clear_line(0);
        lcd::clear_line(1);
        // Update current distance
        // if (targetDistance > 0) {
        //     currentDistance = -degreesToInches(middle_left_wheels.get_position());
        // } else {
        //     currentDistance = degreesToInches(middle_right_wheels.get_position());
        // }
        currentDistance = -degreesToInches((middle_left_wheels.get_position() + middle_right_wheels.get_position())/2.0);
        // currentDistance = ((wheelDiameter * 3.1415926535897) / 360.0) * (middle_left_wheels.get_position() + middle_right_wheels.get_position()) / 2.0;
        // currentDistance = -currentDistance;
        // currentDistance = -degreesToInches(getAverageEncoderValue(true));
        

        double error = fabs(targetDistance) - fabs(currentDistance);

        // Debug prints
        // printf("Current Distance: %f inches\n", currentDistance);
        // printf("Error: %f inches\n", error);
        lcd::print(0, "Current Distance: %f inches\n", currentDistance);
        lcd::print(1, "Error: %f inches\n", error);
        master.print(0, 0, "Dist: %f inches\n", currentDistance);
        master.print(1, 0, "Error: %f in\n", error);
        
        //the error lies here
        if (fabs(error) < 3.0) {
            leftSpeed *= 0.5;
            rightSpeed *= 0.5;
        }

        if (fabs(error) < 1.0) { 
            leftSpeed = 0;
            rightSpeed = 0;

            // left side
            front_left_wheels.brake();
            middle_left_wheels.brake();
            back_left_wheels.brake();
            top_front_left_wheels.brake();
            top_back_left_wheels.brake();

            // right side
            front_right_wheels.brake();
            middle_right_wheels.brake();
            back_right_wheels.brake();
            top_front_right_wheels.brake();
            top_back_right_wheels.brake();
        
            break;
        }

        // Only accumulate integral when error is within a reasonable range
        if (fabs(error) < 10.0 && fabs(error) > 0.5) { // Avoid windup for large errors
            integral += error;
        } else {
            integral = 0; // Reset if error is too large
        }

        // Clamp the integral term to prevent excessive accumulation
        integral = std::max(-integralMax, std::min(integral, integralMax));
        // integral += error;
        if (integral > integralMax) { // Anti-windup
            integral = integralMax;
        } else if (integral < -integralMax) {
            integral = -integralMax;
        }
        double derivative = error - previousError;

        // Compute PID control value
        int controlSignal = local_kp * error + ki * integral + kd * derivative;

        // Apply control signal to motors, limiting to maxSpeed
        leftSpeed = std::min(maxSpeed, std::max(-maxSpeed, controlSignal));
        rightSpeed = std::min(maxSpeed, std::max(-maxSpeed, controlSignal));

        if (targetDistance > 0) {
            leftSpeed = -leftSpeed;
            rightSpeed = -rightSpeed;
        }
        // leftSpeed = -leftSpeed;
        // rightSpeed = -rightSpeed;

        // //the error lies here
        // if (fabs(error) < 3.0) {
        //     leftSpeed *= 0.5;
        //     rightSpeed *= 0.5;
        // }

        // if (fabs(error) < 1.0) { 
        //     leftSpeed = 0;
        //     rightSpeed = 0;

        //     // left side
        //     front_left_wheels.brake();
        //     middle_left_wheels.brake();
        //     back_left_wheels.brake();
        //     top_front_left_wheels.brake();
        //     top_back_left_wheels.brake();

        //     // right side
        //     front_right_wheels.brake();
        //     middle_right_wheels.brake();
        //     back_right_wheels.brake();
        //     top_front_right_wheels.brake();
        //     top_back_right_wheels.brake();
        
        //     break;
        // }


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
    front_left_wheels.brake();
    middle_left_wheels.brake();
    back_left_wheels.brake();
    top_front_left_wheels.brake();
    top_back_left_wheels.brake();

    // right side
    front_right_wheels.brake();
    middle_right_wheels.brake();
    back_right_wheels.brake();
    top_front_right_wheels.brake();
    top_back_right_wheels.brake();

    return;
}

// Function to turn the robot using PID control
void turnPID(double targetDegrees, int maxSpeed) {
    double kp = 1.0;  // Proportional constant (tuned for inches)
    double ki = 0.002;  // Integral constant (set to 0 initially, typically less used for basic moves)
    double kd = 0.1; // Derivative constant (adjusted)
    double currentDegrees = 0; 
    double previousError = 0;
    double integral = 0;
    double integralMax = 100; // Maximum value for integral term
    double local_kp = kp;
    double leftSpeed;
    double rightSpeed;

    resetEncoders();

    // Adjust PID constants dynamically for short distances
    if (targetDegrees < 10) { // For distances less than 10 inches
        local_kp *= 1.5; // Increase proportional gain
        maxSpeed = std::max(50, maxSpeed / 2); // Limit max speed
    }

    while (fabs(currentDegrees) < fabs(targetDegrees) * 2) {
        lcd::clear_line(0);
        lcd::clear_line(1);
        // master.clear();
        // Update current degrees
        currentDegrees = (fabs(front_left_wheels.get_position()) + fabs(front_right_wheels.get_position())) / 2.0;
        

        double error = fabs(targetDegrees) - fabs(currentDegrees);

        // Debug prints
        // printf("Current Degrees: %f inches\n", currentDegrees);
        // printf("Error: %f degrees\n", error);
        lcd::print(0, "Current rotation: %f degrees\n", currentDegrees);
        lcd::print(1, "Error: %f degrees\n", error);
        master.print(0, 0, "Current: %f degrees\n", currentDegrees);
        master.print(1, 0, "Error: %f degrees\n", error);
        
        //the error lies here
        // if (fabs(error) < 3.0) {
        //     leftSpeed *= 0.5;
        //     rightSpeed *= 0.5;
        // }

        if (fabs(error) < 1.0) { 
            leftSpeed = 0;
            rightSpeed = 0;

            // left side
            front_left_wheels.brake();
            middle_left_wheels.brake();
            back_left_wheels.brake();
            top_front_left_wheels.brake();
            top_back_left_wheels.brake();

            // right side
            front_right_wheels.brake();
            middle_right_wheels.brake();
            back_right_wheels.brake();
            top_front_right_wheels.brake();
            top_back_right_wheels.brake();
        
            break;
        }

        // Only accumulate integral when error is within a reasonable range
        if (fabs(error) <= 20) { // Avoid windup for large errors
            integral += error;
        } else {
            integral = 0; // Reset if error is too large
        }

        // Clamp the integral term to prevent excessive accumulation
        integral = std::max(-integralMax, std::min(integral, integralMax));
        // integral += error;
        // if (integral > integralMax) { // Anti-windup
        //     integral = integralMax;
        // } else if (integral < -integralMax) {
        //     integral = -integralMax;
        // }
        double derivative = error - previousError;

        // Compute PID control value
        int controlSignal = local_kp * error + ki * integral + kd * derivative;

        // Apply control signal to motors, limiting to maxSpeed
        leftSpeed = -1 * std::min(maxSpeed, std::max(-maxSpeed, controlSignal));
        rightSpeed = std::min(maxSpeed, std::max(-maxSpeed, controlSignal));

        if (targetDegrees > 0) {
            leftSpeed = -leftSpeed;
            rightSpeed = -rightSpeed;
        }
        // leftSpeed = -leftSpeed;
        // rightSpeed = -rightSpeed;

        // //the error lies here
        // if (fabs(error) < 3.0) {
        //     leftSpeed *= 0.5;
        //     rightSpeed *= 0.5;
        // }

        // if (fabs(error) < 1.0) { 
        //     leftSpeed = 0;
        //     rightSpeed = 0;

        //     // left side
        //     front_left_wheels.brake();
        //     middle_left_wheels.brake();
        //     back_left_wheels.brake();
        //     top_front_left_wheels.brake();
        //     top_back_left_wheels.brake();

        //     // right side
        //     front_right_wheels.brake();
        //     middle_right_wheels.brake();
        //     back_right_wheels.brake();
        //     top_front_right_wheels.brake();
        //     top_back_right_wheels.brake();
        
        //     break;
        // }


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

        delay(10); 
    }

    // Stop motors
    // left side
    front_left_wheels.brake();
    middle_left_wheels.brake();
    back_left_wheels.brake();
    top_front_left_wheels.brake();
    top_back_left_wheels.brake();

    // right side
    front_right_wheels.brake();
    middle_right_wheels.brake();
    back_right_wheels.brake();
    top_front_right_wheels.brake();
    top_back_right_wheels.brake();

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