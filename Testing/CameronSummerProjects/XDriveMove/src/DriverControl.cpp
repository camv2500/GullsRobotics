#include "robot-config.h"
#include "AutonFunctions.h"
#include "DriverControl.h"

using namespace pros;

// Constants

// const int Intake_Speed = 100; // Percentage intake motor speed
// const int Lift_Speed = 100; // Percentage Lift motor speed

// Variables

int BrakeButton; // Variable defined for brake button

// // Variables defined for intake direction
// int Intake_in;  // Takes in the discs
// int Intake_out; // Releases discs

// // Boolean logic for double tap intake ability
// bool continuous_in = false;
// bool continuous_out = false;

// bool lift_press_up = false;
// bool lift_press_down = false;

// Functions

// // Function for intake double tap, keeps track of interval between presses, called as interupt
// int lastPressIN = 0;
// int timeThresholdIN = 250;
// void ContinuousIntakeDoubleTap() {

//   int time = millis(); 
//   int interval = time - lastPressIN;
//   if (interval < timeThresholdIN) {

//     continuous_in = !continuous_in;

//   }

//   lastPressIN = time;
//   delay(20);

// }

// // Function for outtake double tap, keeps track of interval between presses, called as interupt
// int lastPressOUT = 0;
// int timeThresholdOUT = 250; 
// void ContinuousOuttakeDoubleTap() {

//   int time = millis();
//   int interval = time - lastPressOUT;
//   if (interval < timeThresholdOUT) {

//     continuous_out = !continuous_out;

//   } 

//   lastPressOUT = time;
//   delay(20);

// }

void control() {

    while (true) {
        
        BrakeButton = master.get_digital(E_CONTROLLER_DIGITAL_B);

        // if (master.get_digital(E_CONTROLLER_DIGITAL_L1)) {
        //     ContinuousIntakeDoubleTap();
        // }

        // if (master.get_digital(E_CONTROLLER_DIGITAL_L2)) {
        //     ContinuousOuttakeDoubleTap();
        // }

        // if (master.get_digital(E_CONTROLLER_DIGITAL_R1)) {
        //     lift_press_up = true;
        // }
        // else {
        //     lift_press_up = false;
        // }

        // if (master.get_digital(E_CONTROLLER_DIGITAL_R2)) {
        //     lift_press_down = true;
        // }
        // else {
        //     lift_press_down = false;
        // }

        delay(10);
    }
}

void driver() {

    while (true) {
        
        // if (!BrakeButton) {
            
        //     // Calculate the raw sums of appropriate joystick axes
        //     double front_left = (double)(master.get_analog(ANALOG_LEFT_Y) + master.get_analog(ANALOG_LEFT_X) + master.get_analog(ANALOG_RIGHT_X));
        //     double rear_left = (double)(master.get_analog(ANALOG_LEFT_Y) - master.get_analog(ANALOG_LEFT_X) + master.get_analog(ANALOG_RIGHT_X));
        //     double front_right = (double)(master.get_analog(ANALOG_LEFT_Y) - master.get_analog(ANALOG_LEFT_X) - master.get_analog(ANALOG_RIGHT_X));
        //     double rear_right = (double)(master.get_analog(ANALOG_LEFT_Y) + master.get_analog(ANALOG_LEFT_X) - master.get_analog(ANALOG_RIGHT_X));

        //     // Find the largest raw sum or 100
        //     double max_raw_value = std::max(front_left,std::max(rear_left,std::max(front_right,std::max(rear_right,100.0))));

        //     // Scale down each value if there was one larger than 100, otherwise leave them alone
        //     // The largest value will be scaled down to 100, and the others will be reduced by the same factor
        //     front_left = front_left / max_raw_value * 100;
        //     rear_left = rear_left / max_raw_value * 100;
        //     front_right = front_right / max_raw_value * 100;
        //     rear_right = rear_right / max_raw_value * 100;

        //     // Write the scaled sums out to the various motors
        //     FrontL.move(front_left/3);
        //     RearL.move(rear_left/3);
        //     FrontR.move(front_right/3);
        //     RearR.move(rear_right/3);

        // }

        if (!BrakeButton) {

          //Get the raw sums of the X and Y joystick axes
          double front_left  = (double)(master.get_analog(ANALOG_LEFT_Y) + master.get_analog(ANALOG_LEFT_X));
          double back_left   = (double)(master.get_analog(ANALOG_LEFT_Y) - master.get_analog(ANALOG_LEFT_X));
          double front_right = (double)(master.get_analog(ANALOG_LEFT_Y) - master.get_analog(ANALOG_LEFT_X));
          double back_right  = (double)(master.get_analog(ANALOG_LEFT_Y) + master.get_analog(ANALOG_LEFT_X));
          
          //Find the largest possible sum of X and Y
          double max_raw_sum = (double)(abs(master.get_analog(ANALOG_LEFT_Y)) + abs(master.get_analog(ANALOG_LEFT_X)));
          
          //Find the largest joystick value
          double max_XYstick_value = (double)(std::max(abs(master.get_analog(ANALOG_LEFT_Y)),abs(master.get_analog(ANALOG_LEFT_X))));
          
          //The largest sum will be scaled down to the largest joystick value, and the others will be
          //scaled by the same amount to preserve directionality
          if (max_raw_sum != 0) {
              front_left  = front_left / max_raw_sum * max_XYstick_value;
              back_left   = back_left / max_raw_sum * max_XYstick_value;
              front_right = front_right / max_raw_sum * max_XYstick_value;
              back_right  = back_right / max_raw_sum * max_XYstick_value;
          }
          
          //Now to consider rotation
          //Naively add the rotational axis
          front_left  = front_left  + master.get_analog(ANALOG_RIGHT_X);
          back_left   = back_left   + master.get_analog(ANALOG_RIGHT_X);
          front_right = front_right - master.get_analog(ANALOG_RIGHT_X);
          back_right  = back_right  - master.get_analog(ANALOG_RIGHT_X);
          
          //What is the largest sum, or is 100 larger?
          max_raw_sum = std::max(std::abs(front_left),std::max(std::abs(back_left),std::max(std::abs(front_right),std::max(std::abs(back_right),100.0))));
          
          //Scale everything down by the factor that makes the largest only 100, if it was over
          front_left  = front_left  / max_raw_sum * 100.0;
          back_left   = back_left   / max_raw_sum * 100.0;
          front_right = front_right / max_raw_sum * 100.0;
          back_right  = back_right  / max_raw_sum * 100.0;
          
          //Write the manipulated values out to the motors
            FrontL.move(front_left);
            RearL.move(back_left);
            FrontR.move(front_right);
            RearR.move(back_right);

        }

        else {

            FrontL.brake();
            RearL.brake();
            FrontR.brake();
            RearR.brake();

        }

    delay(20);
    
    }

}

// void intake(void) {

//   while(true) {

//     if (continuous_in) {

//       Intake.move(Intake_Speed);

//       if (Intake_out) {

//         continuous_in = false;

//       }

//     }

//     else if (continuous_out) {

//       if (continuous_out) {

//         Intake.move(Intake_Speed/-1);

//         if (Intake_in) {

//           continuous_out = false;

//         }

//       }

//     }

//     else {

//       if (Intake_in && Intake_out) {

//         Intake.brake();

//       }
      
//       else if (Intake_in && !Intake_out) {

//         Intake.move(Intake_Speed);
        
//       }

//       else if (Intake_out && !Intake_in) {

//         Intake.move(Intake_Speed/-1);

//       }

//       else {

//         Intake.brake();

//       }

//     }

//     delay(20);

//   }
  
// }

// void lift(void) {

//     while (true) {
//         if (lift_press_up) {
//             Lift.move(Lift_Speed);
//         }
        
//         else if (lift_press_down) {
//             Lift.move(Lift_Speed/-1);
//         }
//         else {
//             Lift.brake();
//         }

//         delay(20);

//     }

// }