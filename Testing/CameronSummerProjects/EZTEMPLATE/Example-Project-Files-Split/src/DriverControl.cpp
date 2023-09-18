#include "robot-config.h"
#include "AutonFunctions.hpp"
#include "DriverControl.h"

using namespace pros;

// Variables

// int BrakeButton;

// Functions
void control() {

    // while (true) {
        
    //     BrakeButton = master.get_digital(E_CONTROLLER_DIGITAL_B);

    //     delay(10);
    // }
}

void driver() {

    // This is preference to what you like to drive on.
    chassis.set_drive_brake(MOTOR_BRAKE_COAST);

    while (true) {

        chassis.tank(); // Tank control
        // chassis.arcade_standard(ez::SPLIT); // Standard split arcade
        // chassis.arcade_standard(ez::SINGLE); // Standard single arcade
        // chassis.arcade_flipped(ez::SPLIT); // Flipped split arcade
        // chassis.arcade_flipped(ez::SINGLE); // Flipped single arcade

        // . . .
        // Put more user control code here!
        // . . .

        pros::delay(ez::util::DELAY_TIME); // This is used for timer calculations!  Keep this ez::util::DELAY_TIME
    }
    
    // while (true) {
    //     if (!BrakeButton) {
            
    //         // Calculate the raw sums of appropriate joystick axes
    //         double front_left = (double)(master.get_analog(ANALOG_LEFT_Y) + master.get_analog(ANALOG_LEFT_X) + master.get_analog(ANALOG_RIGHT_X));
    //         double rear_left = (double)(master.get_analog(ANALOG_LEFT_Y) - master.get_analog(ANALOG_LEFT_X) + master.get_analog(ANALOG_RIGHT_X));
    //         double front_right = (double)(master.get_analog(ANALOG_LEFT_Y) - master.get_analog(ANALOG_LEFT_X) - master.get_analog(ANALOG_RIGHT_X));
    //         double rear_right = (double)(master.get_analog(ANALOG_LEFT_Y) + master.get_analog(ANALOG_LEFT_X) - master.get_analog(ANALOG_RIGHT_X));

    //         // Find the largest raw sum or 100
    //         double max_raw_value = std::max(front_left,std::max(rear_left,std::max(front_right,std::max(rear_right,100.0))));

    //         // Scale down each value if there was one larger than 100, otherwise leave them alone
    //         // The largest value will be scaled down to 100, and the others will be reduced by the same factor
    //         front_left = front_left / max_raw_value * 100;
    //         rear_left = rear_left / max_raw_value * 100;
    //         front_right = front_right / max_raw_value * 100;
    //         rear_right = rear_right / max_raw_value * 100;

    //         // Write the scaled sums out to the various motors
    //         FrontL.move(front_left/3);
    //         RearL.move(rear_left/3);
    //         FrontR.move(front_right/3);
    //         RearR.move(rear_right/3);

    //     }

    //     else {

    //         FrontL.brake();
    //         RearL.brake();
    //         FrontR.brake();
    //         RearR.brake();

    //     }

    // }

    // delay(20);
}