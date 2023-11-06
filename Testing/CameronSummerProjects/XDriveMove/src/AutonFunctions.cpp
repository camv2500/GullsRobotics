#include "robot-config.h"
#include "AutonFunctions.h"
#include "DriverControl.h"

using namespace pros;

/////////////////////////////////////////////////////////////////////////////////////
//////                              GLOBAL CONSTANTS                           //////
/////////////////////////////////////////////////////////////////////////////////////

const int countsPerRev = 360;
// const double wheelDiameter(4.125); // Inches
const double wheelDiameter(2.75); // Inches
// const double wheelDiameter(3.75); // Inches
const double Pi(3.14159265358979);
const double driveRatio(1);
const double wheelCircumference = wheelDiameter*Pi; // 8.33
const double inchesPerDegree = wheelCircumference/countsPerRev;
const double TURNING_DIAMETER = 10.75;

/////////////////////////////////////////////////////////////////////////////////////
//////                               GLOBAL VARIABLES                          //////
/////////////////////////////////////////////////////////////////////////////////////

float kp, ki, kd, bias, kpT, kiT, kdT;
float error, prevError, derivative, totalError, integralError, prevIntegral, iterationTime;
float leftDist, rightDist, distanceAvg;

/////////////////////////////////////////////////////////////////////////////////////
//////                               OTHER VARIABLES                           //////
/////////////////////////////////////////////////////////////////////////////////////

bool master_auton_enable = true;
bool perma_lock = false;

/////////////////////////////////////////////////////////////////////////////////////
//////                                 FUNCTIONS                               //////
/////////////////////////////////////////////////////////////////////////////////////

// AI
// Function to reset the motor encoders
void resetEncoders() {
    FrontL.tare_position();
    RearL.tare_position();
    FrontR.tare_position();
    RearR.tare_position();
}

// Function to get the average encoder value of the X-Drive
double getAverageEncoderValue(bool ab = false) {
  if (ab) {
    return (fabs(FrontL.get_position()) + fabs(RearL.get_position()) + fabs(FrontR.get_position()) + fabs(RearR.get_position())) / 4.0;
  }
  else {
    return (FrontL.get_position() + RearL.get_position() + FrontR.get_position() + RearR.get_position()) / 4.0;
  }
}

// Function to move the X-Drive laterally using PID
void moveXDriveLaterally(double targetDistance) {
    resetEncoders();

    double error, lastError = 0, integral = 0, derivative;
    double targetRotations = targetDistance / wheelCircumference;

    while (true) {
        // Calculate the error (difference between the target and current position)
        double currentPosition = getAverageEncoderValue() / 360.0;
        error = targetRotations - currentPosition;

        // Calculate the integral term (sum of past errors)
        integral += error;

        // Limit the integral term to prevent windup
        if (integral > 100) {
            integral = 100;
        } else if (integral < -100) {
            integral = -100;
        }

        // Calculate the derivative term (rate of change of the error)
        derivative = error - lastError;
        lastError = error;

        // Calculate the PID output (motor power)
        double output = (kp * error) + (ki * integral) + (kd * derivative);

        // Apply the PID output to the X-Drive motors
        FrontL.move(output);
        RearL.move(-output);
        FrontR.move(-output);
        RearR.move(output);

        // Check if the X-Drive has reached the target distance
        if (fabs(error) < 0.5) { // You can adjust the tolerance as needed
            break;
        }

        delay(20); // Wait for a short duration before the next iteration
    }

    // Stop the X-Drive motors once the target distance is reached
    FrontL.move(0);
    RearL.move(0);
    FrontR.move(0);
    RearR.move(0);
}
void chatGPTPID(double target) {

    kp = 30.00; // 30.00
    ki = 0.00;
    kd = 0.00;
    moveXDriveLaterally(target);
  
}
// End AI

// Function to get the average encoder value of the X-Drive
double getAverageTrackerValue(bool ab = false) {
  if (ab) {
    return (fabs(TrackL.get_position()) + fabs(TrackR.get_position())) / 2.0;
  }
  else {
    return (TrackL.get_position() + TrackR.get_position()) / 2.0;
  }
}

/*

INFORMATION REGARDING PID (Proportional Integral Derivative) LOOPS, FUNCTIONS, AND MORE:

  kP INFORMATION:

    - kP does most of the work, but using it on its own can cause the robot to fall a bit short
    - kP should NEVER be greater than 1

  kI INFORMATION:

    - kI gets rid of undershoot, but it can quickly spiral out of control and cause overshoot if not used carefully
    - If kI is above 0 and you are experiencing overshoot/oscillation issues, just don't use kI
    
  kD INFORMATION:

   - kD servers as a dampener that makes motions when the robot is closer to the target less jerky, in a sense
   - kD should never exceed .05 UNLESS you're use PID for fully controlling an arm (AKA not as a brake), in which your cap should be .15

  * For VEX, PID is a helpful tool that allows for more consistent results and better accuracy
  * Beware that setting the control constants kP, kI, and kD too high or to the wrong settings can cause undesirable, painful results
  * If to make something work you have set any of these constants to something outside of these bounds, it is likely a problem not related to the code.

*/

void LateralPID(double x, double y) { // Use motor rotations and encoders to move a specified distance
  // @param if runIntake is true, run the intakes while the robot is moving when it's not, it stops the intake

  if (x == 0 && y == 0) {
    lcd::print(2, "You are an idiot!!!");
    master.print(1, 0, "You are an idiot!!!");
    return;
  }

  // if (master_auton_enable) {

    kp = 30.50; // 3.50
    ki = 0.0005; // 10.00
    kd = 0.0495; // 0.00

    double error, lastError = 0, integral = 0, derivative;
    double error2, lastError2 = 0, integral2 = 0, derivative2;

    double travelInches = (x*x) + (y*y);
    travelInches = sqrt(travelInches);
    double Rotations = travelInches / wheelCircumference;
    double dist = 0; // Variable that will be current distance
    double lateralMotorSpeed;
    double lateralMotorSpeed2;

    // FrontL.resetRotation();
    // rightDrive.resetRotation();
    FrontL.tare_position();
    FrontR.tare_position();
    RearL.tare_position();
    RearR.tare_position();

    if (x != 0) {
    // if (/*y >= 0*/ true) {

      while (dist <= fabs(x)) { // Proportional control feedback loop for error

        // lateralMotorSpeed = (travelInches - dist)*(127/100)*kp;
        // lateralMotorSpeed = (double)((y + x) - dist)*(127/100)*kp;
        // lateralMotorSpeed2 = (double)((y - x) - dist)*(127/100)*kp;

        // dist = ((FrontL.get_position()*3.14*wheelDiameter) + (FrontR.get_position()*3.14*wheelDiameter)) / 2; // pi * diameter // Distance = total rotations * circumference of 1 rotation
        if (x < 0)
          dist = -(getAverageEncoderValue(true)) / 360.0; // pi * diameter // Distance = total rotations * circumference of 1 rotation
        else
          dist = getAverageEncoderValue(true) / 360.0; // pi * diameter // Distance = total rotations * circumference of 1 rotation
        
        error = (double)(x / wheelCircumference) - dist;
        // error2 = (double)((y - x) / wheelCircumference) - dist;

        // Calculate the integral term (sum of past errors)
        integral += error;
        // integral2 += error2;

        // Limit the integral term to prevent windup
        if (integral > 5000) {
            integral = 5000;
        } else if (integral < -5000) {
            integral = -5000;
        }
        // if (integral2 > 5000) {
        //     integral2 = 5000;
        // } else if (integral2 < -5000) {
        //     integral2 = -5000;
        // }

        // Calculate the derivative term (rate of change of the error)
        derivative = error - lastError;
        lastError = error;
        // derivative2 = error2 - lastError2;
        // lastError2 = error2;

        lateralMotorSpeed = (kp * error) + (ki * integral) + (kd * derivative);
        // lateralMotorSpeed2 = (kp * error2) + (ki * integral2) + (kd * derivative2);
        
        // leftDrive.spin(forward, lateralMotorSpeed, pct);
        // rightDrive.spin(forward, lateralMotorSpeed, pct);
        // double front_left = (double)(y + x);
        // double rear_left = (double)(y - x);
        // double front_right = (double)(y - x);
        // double rear_right = (double)(y + x);

        // // Find the largest raw sum or 100
        // double max_raw_value = std::max(front_left,std::max(rear_left,std::max(front_right,std::max(rear_right,100.0))));

        // // Scale down each value if there was one larger than 100, otherwise leave them alone
        // // The largest value will be scaled down to 100, and the others will be reduced by the same factor
        // front_left = front_left / max_raw_value * 100;
        // rear_left = rear_left / max_raw_value * 100;
        // front_right = front_right / max_raw_value * 100;
        // rear_right = rear_right / max_raw_value * 100;

        // // Write the scaled sums out to the various motors
        // FrontL.move(front_left/3);
        // RearL.move(rear_left/3);
        // FrontR.move(front_right/3);
        // RearR.move(rear_right/3);

        // if (x >= 0) {
        //   FrontL.move(lateralMotorSpeed);
        //   RearL.move(-lateralMotorSpeed);
        //   FrontR.move(-lateralMotorSpeed);
        //   RearR.move(lateralMotorSpeed);
        // }
        // else if (x < 0) {
        //   FrontL.move(-lateralMotorSpeed);
        //   RearL.move(lateralMotorSpeed);
        //   FrontR.move(lateralMotorSpeed);
        //   RearR.move(-lateralMotorSpeed);
        // }

          FrontL.move(lateralMotorSpeed);
          RearL.move(-lateralMotorSpeed);
          FrontR.move(-lateralMotorSpeed);
          RearR.move(lateralMotorSpeed);

          // lcd::print(2, "%lf", lateralMotorSpeed);
          lcd::print(2, "%lf", fabs(fabs(x) - dist));
          // master.print(1, 0, "%lf", fabs(fabs(x) - dist));
          lcd::print(3, "%lf", dist);
          master.print(1, 0, "%lf", lateralMotorSpeed);

        delay(20);

        // dist = FrontL.get_actual_velocity()*3.14*wheelDiameter;
        
        if (fabs(fabs(x) - dist) <= (fabs(0.5)) || fabs(lateralMotorSpeed) <= (fabs(9.5))) {  

          break; 

        }


      }

    FrontL.move(0);
    RearL.move(0);
    FrontR.move(0);
    RearR.move(0);

    dist = 0;

    FrontL.tare_position();
    FrontR.tare_position();
    RearL.tare_position();
    RearR.tare_position();

    lcd::print(2, "Exited X loop");
    master.print(1, 0, "Exited X loop");

    }

    if (y != 0) {
      while (dist <= fabs(y)) { // Proportional control feedback loop for error

        // lateralMotorSpeed = (travelInches - dist)*(127/100)*kp;
        // lateralMotorSpeed = (double)((y + x) - dist)*(127/100)*kp;
        // lateralMotorSpeed2 = (double)((y - x) - dist)*(127/100)*kp;

        // dist = ((FrontL.get_position()*3.14*wheelDiameter) + (FrontR.get_position()*3.14*wheelDiameter)) / 2; // pi * diameter // Distance = total rotations * circumference of 1 rotation
        if (y < 0)
          dist = -(getAverageEncoderValue(true)) / 360.0; // pi * diameter // Distance = total rotations * circumference of 1 rotation
        else
          dist = getAverageEncoderValue(true) / 360.0; // pi * diameter // Distance = total rotations * circumference of 1 rotation
        
        error = (double)(y / wheelCircumference) - dist;
        // error2 = (double)((y - x) / wheelCircumference) - dist;

        // Calculate the integral term (sum of past errors)
        integral += error;
        // integral2 += error2;

        // Limit the integral term to prevent windup
        if (integral > 5000) {
            integral = 5000;
        } else if (integral < -5000) {
            integral = -5000;
        }
        // if (integral2 > 5000) {
        //     integral2 = 5000;
        // } else if (integral2 < -5000) {
        //     integral2 = -5000;
        // }

        // Calculate the derivative term (rate of change of the error)
        derivative = error - lastError;
        lastError = error;
        // derivative2 = error2 - lastError2;
        // lastError2 = error2;

        lateralMotorSpeed = (kp * error) + (ki * integral) + (kd * derivative);
        // lateralMotorSpeed2 = (kp * error2) + (ki * integral2) + (kd * derivative2);
        
        // leftDrive.spin(forward, lateralMotorSpeed, pct);
        // rightDrive.spin(forward, lateralMotorSpeed, pct);
        // double front_left = (double)(y + x);
        // double rear_left = (double)(y - x);
        // double front_right = (double)(y - x);
        // double rear_right = (double)(y + x);

        // // Find the largest raw sum or 100
        // double max_raw_value = std::max(front_left,std::max(rear_left,std::max(front_right,std::max(rear_right,100.0))));

        // // Scale down each value if there was one larger than 100, otherwise leave them alone
        // // The largest value will be scaled down to 100, and the others will be reduced by the same factor
        // front_left = front_left / max_raw_value * 100;
        // rear_left = rear_left / max_raw_value * 100;
        // front_right = front_right / max_raw_value * 100;
        // rear_right = rear_right / max_raw_value * 100;

        // // Write the scaled sums out to the various motors
        // FrontL.move(front_left/3);
        // RearL.move(rear_left/3);
        // FrontR.move(front_right/3);
        // RearR.move(rear_right/3);

        // if (x >= 0) {
        //   FrontL.move(lateralMotorSpeed);
        //   RearL.move(-lateralMotorSpeed);
        //   FrontR.move(-lateralMotorSpeed);
        //   RearR.move(lateralMotorSpeed);
        // }
        // else if (x < 0) {
        //   FrontL.move(-lateralMotorSpeed);
        //   RearL.move(lateralMotorSpeed);
        //   FrontR.move(lateralMotorSpeed);
        //   RearR.move(-lateralMotorSpeed);
        // }

          FrontL.move(lateralMotorSpeed);
          RearL.move(lateralMotorSpeed);
          FrontR.move(lateralMotorSpeed);
          RearR.move(lateralMotorSpeed);

        delay(20);

        // dist = FrontL.get_actual_velocity()*3.14*wheelDiameter;
        
        if (fabs(fabs(y) - dist) <= (fabs(0.5)) || fabs(lateralMotorSpeed) <= (fabs(9.5))) {  

          break; 

        }


      }

      lcd::print(2, "Exited Y loop");
      master.print(1, 0, "Exited Y loop");

    }
  
    // else if (y < 0) {

    //   while (dist >= travelInches) { // Proportional control feedback loop for error

    //     // if (measureAndUltras(4, 4, 1)) {
    //     //   break;
    //     // }
    //     // if (measureAndUltras(3.5, 3.5, 1)) {
    //     //   break;
    //     // }

    //     // lateralMotorSpeed = (-travelInches + dist)*(127/100)*kp;
    //     // lateralMotorSpeed = (double)(-(y + x) + dist)*(127/100)*kp;
    //     // lateralMotorSpeed2 = (double)(-(y - x) + dist)*(127/100)*kp;

    //     dist = getAverageEncoderValue() / 360.0; // pi * diameter // Distance = total rotations * circumference of 1 rotation
    //     error = (double)(-((y + x) / wheelCircumference)) + dist;
    //     error2 = (double)(-((y - x) / wheelCircumference)) + dist;

    //     // Calculate the integral term (sum of past errors)
    //     integral += error;
    //     integral2 += error2;

    //     // Limit the integral term to prevent windup
    //     if (integral > 5000) {
    //         integral = 5000;
    //     } else if (integral < -5000) {
    //         integral = -5000;
    //     }
    //     if (integral2 > 5000) {
    //         integral2 = 5000;
    //     } else if (integral2 < -5000) {
    //         integral2 = -5000;
    //     }

    //     // Calculate the derivative term (rate of change of the error)
    //     derivative = error - lastError;
    //     lastError = error;
    //     derivative2 = error2 - lastError2;
    //     lastError2 = error2;

    //     lateralMotorSpeed = (kp * error) + (ki * integral) + (kd * derivative);
    //     lateralMotorSpeed2 = (kp * error2) + (ki * integral2) + (kd * derivative2);

    //     // leftDrive.spin(reverse, lateralMotorSpeed, pct);
    //     // rightDrive.spin(reverse, lateralMotorSpeed, pct);
        
    //     // double front_left = (double)(y + x);
    //     // double rear_left = (double)(y - x);
    //     // double front_right = (double)(y - x);
    //     // double rear_right = (double)(y + x);

    //     // // Find the largest raw sum or 100
    //     // double max_raw_value = std::max(front_left,std::max(rear_left,std::max(front_right,std::max(rear_right,100.0))));

    //     // // Scale down each value if there was one larger than 100, otherwise leave them alone
    //     // // The largest value will be scaled down to 100, and the others will be reduced by the same factor
    //     // front_left = front_left / max_raw_value * 100;
    //     // rear_left = rear_left / max_raw_value * 100;
    //     // front_right = front_right / max_raw_value * 100;
    //     // rear_right = rear_right / max_raw_value * 100;

    //     // // Write the scaled sums out to the various motors
    //     // FrontL.move(front_left/3);
    //     // RearL.move(rear_left/3);
    //     // FrontR.move(front_right/3);
    //     // RearR.move(rear_right/3);

    //     // if (x >= 0) {
    //     //   FrontL.move(lateralMotorSpeed);
    //     //   RearL.move(-lateralMotorSpeed);
    //     //   FrontR.move(-lateralMotorSpeed);
    //     //   RearR.move(lateralMotorSpeed);
    //     // }
    //     // else if (x < 0) {
    //     //   FrontL.move(-lateralMotorSpeed);
    //     //   RearL.move(lateralMotorSpeed);
    //     //   FrontR.move(lateralMotorSpeed);
    //     //   RearR.move(-lateralMotorSpeed);
    //     // }

    //     FrontL.move(lateralMotorSpeed);
    //     RearL.move(lateralMotorSpeed2);
    //     FrontR.move(lateralMotorSpeed2);
    //     RearR.move(lateralMotorSpeed);

    //     delay(20);

    //     // dist = ((FrontL.get_position()*3.14*wheelDiameter) + (FrontR.get_position()*3.14*wheelDiameter)) / 2; // pi * diameter // Distance = total rotations * circumference of 1 rotation

    //     if (fabs(travelInches - dist) <= (fabs(0.5))) {  

    //       break; 

    //     }

    //   }

    // }

    // Stops motors once target is reached and loop finishes
    // Optional braking, will make motion more fluid
    // FrontL.brake();
    // RearL.brake();
    // FrontR.brake();
    // RearR.brake();
    FrontL.move(0);
    RearL.move(0);
    FrontR.move(0);
    RearR.move(0);

  // }

  delay(50);

}

void TrackerPID(double x, double y, double wp) {
  // @param wp - waypoint

  // This is if the programers call this function without inputting any parameters.
  if (x == 0 && y == 0) {
    lcd::print(2, "You are an idiot!!!");
    master.print(1, 0, "You are an idiot!!!");
    return;
  }

  if (master_auton_enable) {

    kp = 30.50; // 3.50
    // kp = 10.00; // 3.50
    ki = 0.0005; // 10.00
    kd = 0.00; // 0.00 0.0495

    double error, lastError = 0, integral = 0, derivative;
    // double error2, lastError2 = 0, integral2 = 0, derivative2;

    // double travelInches = (x*x) + (y*y);
    // travelInches = sqrt(travelInches);
    // double Rotations = travelInches / wheelCircumference;
    double dist = 0; // Variable that will be current distance
    double lateralMotorSpeed;
    double lateralMotorSpeed2;

    // FrontL.resetRotation();
    // rightDrive.resetRotation();

    // FrontL.tare_position();
    // FrontR.tare_position();
    // RearL.tare_position();
    // RearR.tare_position();

    TrackL.reset_position();
    TrackR.reset_position();

    if (x != 0) {
    // if (/*y >= 0*/ true) {

      while (fabs(dist) <= fabs(x)) { // Proportional control feedback loop for error

        // dist = ((FrontL.get_position()*3.14*wheelDiameter) + (FrontR.get_position()*3.14*wheelDiameter)) / 2; // pi * diameter // Distance = total rotations * circumference of 1 rotation
        if (x < 0)
          dist = (getAverageTrackerValue(true)) / 360.0; // pi * diameter // Distance = total rotations * circumference of 1 rotation
        else
          dist = -getAverageTrackerValue(true) / 360.0; // pi * diameter // Distance = total rotations * circumference of 1 rotation
        
        error = (double)(x / wheelCircumference) - dist;

        // Calculate the integral term (sum of past errors)
        integral += error;
        // integral2 += error2;

        // Limit the integral term to prevent windup
        if (integral > 5000) {
            integral = 5000;
        } else if (integral < -5000) {
            integral = -5000;
        }
        // if (integral2 > 5000) {
        //     integral2 = 5000;
        // } else if (integral2 < -5000) {
        //     integral2 = -5000;
        // }

        // Calculate the derivative term (rate of change of the error)
        derivative = error - lastError;
        lastError = error;

        lateralMotorSpeed = (kp * error) + (ki * integral)  + (kd * derivative);

        // lateralMotorSpeed = -1 * lateralMotorSpeed;

          FrontL.move(lateralMotorSpeed);
          RearL.move(-lateralMotorSpeed);
          FrontR.move(-lateralMotorSpeed);
          RearR.move(lateralMotorSpeed);

          // lcd::print(2, "%lf", lateralMotorSpeed);
          lcd::print(2, "%lf", fabs(fabs(x) - dist));
          // master.print(1, 0, "%lf", fabs(fabs(x) - dist));
          lcd::print(3, "%lf", dist);
          master.print(1, 0, "%lf", lateralMotorSpeed);

        delay(20);

        // dist = FrontL.get_actual_velocity()*3.14*wheelDiameter;
        
        if (fabs(fabs(x) - dist) <= (fabs(0.5)) /*|| fabs(lateralMotorSpeed) <= (fabs(9.5))*/) {  

          break; 

        }


      }

    FrontL.move(0);
    RearL.move(0);
    FrontR.move(0);
    RearR.move(0);

    dist = 0;

    // FrontL.tare_position();
    // FrontR.tare_position();
    // RearL.tare_position();
    // RearR.tare_position();

    TrackL.reset_position();
    TrackR.reset_position();

    lcd::print(2, "Exited X loop");
    master.print(1, 0, "Exited X loop");
    delay(1000);

    }

    if (y != 0) {
      while (fabs(dist) <= fabs(y)) { // Proportional control feedback loop for error

        // lateralMotorSpeed = (travelInches - dist)*(127/100)*kp;
        // lateralMotorSpeed = (double)((y + x) - dist)*(127/100)*kp;
        // lateralMotorSpeed2 = (double)((y - x) - dist)*(127/100)*kp;

        // dist = ((FrontL.get_position()*3.14*wheelDiameter) + (FrontR.get_position()*3.14*wheelDiameter)) / 2; // pi * diameter // Distance = total rotations * circumference of 1 rotation
        if (y < 0)
          dist = (getAverageTrackerValue(true)) / 360.0; // pi * diameter // Distance = total rotations * circumference of 1 rotation
        else
          dist = -getAverageTrackerValue(true) / 360.0; // pi * diameter // Distance = total rotations * circumference of 1 rotation
        
        error = (double)(y / wheelCircumference) - dist;
        // error2 = (double)((y - x) / wheelCircumference) - dist;

        // Calculate the integral term (sum of past errors)
        integral += error;
        // integral2 += error2;

        // Limit the integral term to prevent windup
        if (integral > 5000) {
            integral = 5000;
        } else if (integral < -5000) {
            integral = -5000;
        }
        // if (integral2 > 5000) {
        //     integral2 = 5000;
        // } else if (integral2 < -5000) {
        //     integral2 = -5000;
        // }

        // Calculate the derivative term (rate of change of the error)
        derivative = error - lastError;
        lastError = error;
        // derivative2 = error2 - lastError2;
        // lastError2 = error2;

        lateralMotorSpeed = (kp * error) + (ki * integral)  + (kd * derivative);
        // lateralMotorSpeed2 = (kp * error2) + (ki * integral2) + (kd * derivative2);
        
        // leftDrive.spin(forward, lateralMotorSpeed, pct);
        // rightDrive.spin(forward, lateralMotorSpeed, pct);
        // double front_left = (double)(y + x);
        // double rear_left = (double)(y - x);
        // double front_right = (double)(y - x);
        // double rear_right = (double)(y + x);

        // // Find the largest raw sum or 100
        // double max_raw_value = std::max(front_left,std::max(rear_left,std::max(front_right,std::max(rear_right,100.0))));

        // // Scale down each value if there was one larger than 100, otherwise leave them alone
        // // The largest value will be scaled down to 100, and the others will be reduced by the same factor
        // front_left = front_left / max_raw_value * 100;
        // rear_left = rear_left / max_raw_value * 100;
        // front_right = front_right / max_raw_value * 100;
        // rear_right = rear_right / max_raw_value * 100;

        // // Write the scaled sums out to the various motors
        // FrontL.move(front_left/3);
        // RearL.move(rear_left/3);
        // FrontR.move(front_right/3);
        // RearR.move(rear_right/3);

        // if (x >= 0) {
        //   FrontL.move(lateralMotorSpeed);
        //   RearL.move(-lateralMotorSpeed);
        //   FrontR.move(-lateralMotorSpeed);
        //   RearR.move(lateralMotorSpeed);
        // }
        // else if (x < 0) {
        //   FrontL.move(-lateralMotorSpeed);
        //   RearL.move(lateralMotorSpeed);
        //   FrontR.move(lateralMotorSpeed);
        //   RearR.move(-lateralMotorSpeed);
        // }

          FrontL.move(lateralMotorSpeed);
          RearL.move(lateralMotorSpeed);
          FrontR.move(lateralMotorSpeed);
          RearR.move(lateralMotorSpeed);

        delay(20);

        // dist = FrontL.get_actual_velocity()*3.14*wheelDiameter;
        
        if (fabs(fabs(y) - dist) <= (fabs(0.5)) /*|| fabs(lateralMotorSpeed) <= (fabs(9.5))*/) {  

          break; 

        }


      }

      lcd::print(2, "Exited Y loop");
      master.print(1, 0, "Exited Y loop");

    }

    // Stops motors once target is reached and loop finishes
    // Optional braking, will make motion more fluid
    // FrontL.brake();
    // RearL.brake();
    // FrontR.brake();
    // RearR.brake();
    FrontL.move(0);
    RearL.move(0);
    FrontR.move(0);
    RearR.move(0);

  }

  delay(1000); // 50
}

// Gains are predetermined
// void TurnPID(double degrees) {

//   if (master_auton_enable) {

//     int prevms = Brain.timer(msec);
//     bool esc = false;
//     kp = 0.60;  // 0.50
//     ki = 0.00;  // 0.00
//     kd = 0.005; // 0.065
  
//     bias = 7;
//     prevError = 0;
//     prevIntegral = 0;
//     iterationTime = 10; // ms

//     InertialSensor.resetRotation();
//     double degreesTurned = InertialSensor.rotation();
//     error = degrees; // -------- initial error

//     while (fabs(error) > 1.5 && master_auton_enable && !(esc)) {

//       degreesTurned = InertialSensor.rotation();         

//       error = degrees - degreesTurned;                    // -------- proportion
//       integralError = prevIntegral + error*iterationTime; // -------- integral
//       derivative = error - prevError;                     // -------- derivative

//       float pidMoveMotor = error*kp + totalError*ki + derivative*kd + (bias/100)*127; // Speed for the motors

//       if (degrees < 0) { 

//         pidMoveMotor = error*kp + totalError*ki + derivative*kd + -1*bias;

//       }

//       else {

//         pidMoveMotor = error*kp + totalError*ki + derivative*kd + bias;

//       }

//       float pidMovePCT = (pidMoveMotor/127*100);

//       leftDrive.spin(fwd,pidMovePCT, pct);
//       rightDrive.spin(reverse,pidMovePCT, pct);
       
//       prevError = error;
//       prevIntegral = integralError;
//       vex::task::sleep(iterationTime);

//       int currenttime = Brain.timer(msec);

//       // Force bailout
//       if ((currenttime - prevms) > 5000) {

//         esc = true;

//       }

//     }

    
//     leftDrive.stop(hold); 
//     rightDrive.stop(hold);

//     task::sleep(50);

//   }

// }

void set_master_auton_enable() {

  if (!perma_lock) {

    master_auton_enable = true;

  }

}

void clear_master_auton_enable() {

  if (!perma_lock) {

    master_auton_enable = false;

  }

}

void set_perma_lock() {

  perma_lock = true;

}

void clear_perma_lock() {

  perma_lock = false;

}