#include "robot-config.h"
#include "AutonFunctions.h"
#include "DriverControl.h"

using namespace pros;

void driverControl() {

    while (true) {
        left_wheels.move(master.get_analog(ANALOG_LEFT_Y));
        right_wheels.move(master.get_analog(ANALOG_RIGHT_Y));

    delay(2);
    }
}