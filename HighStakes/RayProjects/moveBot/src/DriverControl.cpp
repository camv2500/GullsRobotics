#include "robot-config.h"
#include "AutonFunctions.h"
#include "DriverControl.h"

using namespace pros;

void driverControl() {
    while (true) {
        // Test with fixed forward values
        back_left_wheels.move(500);
        front_left_wheels.move(500);
        back_right_wheels.move(500);
        middle_right_wheels.move(500);
        middle_left_wheels.move(500);
        front_right_wheels.move(500);
        top_front_right_wheels.move(500);
        top_front_left_wheels.move(500);
        top_back_left_wheels.move(500);
        top_back_right_wheels.move(500);

        delay(5000);
  
        
    }
}


