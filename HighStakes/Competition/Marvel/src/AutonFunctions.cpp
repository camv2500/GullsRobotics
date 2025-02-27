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
    back_left_wheels.tare_position();

    front_right_wheels.tare_position();
    back_right_wheels.tare_position();
}

// Function to get the average encoder value
double getAverageEncoderValue(bool ab = false) {
    if (ab) {
      return (fabs(front_left_wheels.get_position()) + fabs(back_left_wheels.get_position()) + fabs(front_right_wheels.get_position()) + fabs(back_right_wheels.get_position())) / 4.0;
    }
    else {
      return (front_left_wheels.get_position() + back_left_wheels.get_position() + front_right_wheels.get_position() + back_right_wheels.get_position()) / 4.0;
    }
  }

// Function to move the robot laterally using PID control
void lateralPID(double targetDistance, int maxSpeed) {
    double kp = 1.0;  // Proportional constant (tuned for inches) 1.0
    double ki = 0.002;  // Integral constant (set to 0 initially, typically less used for basic moves) 0.002
    double kd = 0.15; // Derivative constant (adjusted) 0.1
    double currentDistance = 0; 
    double previousError = 0;
    double integral = 0;
    double integralMax = 100; // Maximum value for integral term
    double local_kp = kp;
    double leftSpeed;
    double rightSpeed;

    targetDistance = -targetDistance; // Invert target distance for correct direction

    resetEncoders();

    inertial_sensor.tare_rotation();
    delay(200);

    // Adjust PID constants dynamically for short distances
    if (fabs(targetDistance) < 10) { // For distances less than 10 inches
        local_kp *= 1.5; // Increase proportional gain
        maxSpeed = std::max(50, maxSpeed / 2); // Limit max speed
    }

    while (fabs(currentDistance) < fabs(targetDistance) / 1.55) { // Adjust the condition to account for wheel diameter
        lcd::clear_line(0);
        lcd::clear_line(1);
       
        currentDistance = degreesToInches((front_left_wheels.get_position() + front_right_wheels.get_position())/2.0);

        double error = targetDistance - currentDistance;

        // Debug prints
        lcd::print(0, "Current Distance: %f inches\n", currentDistance);
        lcd::print(1, "Error: %f inches\n", error);
        master.print(0, 0, "Dist: %f inches\n", currentDistance);
        // master.print(1, 0, "Error: %f in\n", error);
        // master.print(2, 0, "Left: %f Right: %f", middle_left_wheels.get_position(), middle_right_wheels.get_position());
        master.print(1, 0, "Left: %f", middle_left_wheels.get_position());
        master.print(2, 0, "Right: %f", middle_right_wheels.get_position());
        
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
            back_left_wheels.brake();

            // right side
            front_right_wheels.brake();
            back_right_wheels.brake();
        
            break;
        }

        // Only accumulate integral when error is within a reasonable range
        if (fabs(error) <= 20) { // Avoid windup for large errors
            integral += error;
        } else {
            integral = 0; // Reset if error is too large
        }

        // Clamp the integral term to prevent excessive accumulation
        integral = std::clamp(integral, -integralMax, integralMax);
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
        double headingError = inertial_sensor.get_rotation();
        double correction = headingError * 0.5;  // Adjust correction factor

        int leftControl = controlSignal + correction;
        int rightControl = controlSignal - correction;

        leftSpeed = std::min(maxSpeed, std::max(-maxSpeed, leftControl));
        rightSpeed = std::min(maxSpeed, std::max(-maxSpeed, rightControl));

        // left side 
        front_left_wheels.move(leftSpeed);
        back_left_wheels.move(leftSpeed);

        // right side
        front_right_wheels.move(rightSpeed);
        back_right_wheels.move(rightSpeed);

        previousError = error;

        delay(0.5); 
    }

    // Stop motors
    // left side
    front_left_wheels.brake();
    back_left_wheels.brake();

    // right side
    front_right_wheels.brake();
    back_right_wheels.brake();

    return;
}

// Function to turn the robot using PID control
void turnPID(double targetDegrees, int maxSpeed) {
    double kp = 0.6;  // Proportional constant (tuned for inches)
    double ki = 0.002;  // Integral constant (set to 0 initially, typically less used for basic moves)
    double kd = 0.15; // Derivative constant (adjusted)
    double currentDegrees = 0; 
    double previousError = 0;
    double integral = 0;
    double integralMax = 100; // Maximum value for integral term
    double local_kp = kp;
    double leftSpeed;
    double rightSpeed;

    targetDegrees = -targetDegrees; // Invert target degrees for correct direction

    // resetEncoders();
    // Reset inertial sensor heading
    inertial_sensor.tare_rotation();
    delay(200); // Wait for sensor to stabilize

    // Adjust PID constants dynamically for short distances 
    if (fabs(targetDegrees) <= 45) { // For distances less than 10 inches
        // local_kp *= 1.5; // Increase proportional gain
        local_kp *= 2.0; // Increase proportional gain
        maxSpeed = std::max(50, maxSpeed / 2); // Limit max speed
    }
    else if (fabs(targetDegrees) > 135) {
        local_kp /= 1.25; // Increase proportional gain
        maxSpeed = std::max(50, maxSpeed / 2); // Limit max speed
    }
    
    while (true) {
        lcd::clear_line(0);
        lcd::clear_line(1);
        // master.clear();
        // Update current degrees
        currentDegrees = inertial_sensor.get_rotation();
        if (!std::isfinite(currentDegrees)) currentDegrees = 0;

        double error = targetDegrees - currentDegrees;

        // Debug prints
        lcd::print(0, "Current rotation: %f degrees\n", currentDegrees);
        lcd::print(1, "Error: %f degrees\n", error);
        master.print(0, 0, "Current: %f degrees\n", currentDegrees);
        master.print(1, 0, "Error: %f degrees\n", error);
        
        if (fabs(error) < 5.0) {
            leftSpeed *= 0.7;
            rightSpeed *= 0.7;
        }

        if (fabs(error) < 1.0) { 
            leftSpeed = 0;
            rightSpeed = 0;

            // left side
            front_left_wheels.brake();
            back_left_wheels.brake();

            // right side
            front_right_wheels.brake();
            back_right_wheels.brake();
        
            break;
        }

        // Only accumulate integral when error is within a reasonable range
        if (fabs(error) <= 20) { // Avoid windup for large errors
            integral += error;
        } else {
            integral = 0; // Reset if error is too large
        }

        // Clamp the integral term to prevent excessive accumulation
        integral = std::clamp(integral, -integralMax, integralMax);

        double derivative = error - previousError;

        // Compute PID control value
        int controlSignal = local_kp * error + ki * integral + kd * derivative;

        if (fabs(controlSignal) < 10) {
            if (controlSignal > 0) {
                controlSignal = 10;
            }
            else {
                controlSignal = -10;
            }
        }

        // Apply control signal to motors, limiting to maxSpeed
        leftSpeed = -std::clamp(controlSignal, -maxSpeed, maxSpeed);
        rightSpeed = std::clamp(controlSignal, -maxSpeed, maxSpeed);

        // left side 
        front_left_wheels.move(leftSpeed);
        back_left_wheels.move(leftSpeed);

        // right side
        front_right_wheels.move(rightSpeed);
        back_right_wheels.move(rightSpeed);

        previousError = error;

        delay(10); 
    }

    // Stop motors
    // left side
    front_left_wheels.brake();
    back_left_wheels.brake();

    // right side
    front_right_wheels.brake();
    back_right_wheels.brake();

    return;
}

// Function to turn the robot clockwise for a fixed amount of time
void turnClockwiseTime(int turnTime, int maxSpeed) {
    // Move the robot in opposite directions to turn
    // left side
    front_left_wheels.move(-maxSpeed);
    back_left_wheels.move(-maxSpeed);

    // right side
    front_right_wheels.move(maxSpeed);
    back_right_wheels.move(maxSpeed);

    delay(turnTime);  // Run the motors for the specified time

    // Stop motors after the turn
    // left side
    front_left_wheels.move(0);
    back_left_wheels.move(0);

    // right side
    front_right_wheels.move(0);
    back_right_wheels.move(0);

    return;
}

// Convert from degrees to inches
double degreesToInches(double degrees) {
    double pi = 3.1415926535897;
    double wheelCircumference = wheelDiameter * pi;

    return (degrees / 360.0) * wheelCircumference;
}