#include "robot-config.h"
#include "DriverControl.h"
#include "AutonFunctions.hpp"
#include "Autonomous.h"

using namespace pros;

void Autonomous() {
    chassis.reset_pid_targets(); // Resets PID targets to 0
    chassis.reset_gyro(); // Reset gyro position to 0
    chassis.reset_drive_sensor(); // Reset drive sensors to 0
    chassis.set_drive_brake(MOTOR_BRAKE_HOLD); // Set motors to hold.  This helps autonomous consistency.

    ez::as::auton_selector.call_selected_auton(); // Calls selected auton from autonomous selector.
}