#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor LeftMotor1 = motor(PORT13, ratio6_1, true);
motor RightMotor1 = motor(PORT14, ratio6_1, false);
controller Controller1 = controller(primary);
motor LeftMotor2 = motor(PORT1, ratio6_1, true);
motor LeftMotor3 = motor(PORT2, ratio6_1, true);
motor LeftMotor4 = motor(PORT3, ratio6_1, true);
motor RightMotor2 = motor(PORT4, ratio6_1, false);
motor RightMotor3 = motor(PORT5, ratio6_1, false);
motor RightMotor4 = motor(PORT6, ratio6_1, false);
digital_out magTilt = digital_out(Brain.ThreeWirePort.A);
digital_out indexer = digital_out(Brain.ThreeWirePort.B);
motor fw1 = motor(PORT7, ratio6_1, false);
motor fw2 = motor(PORT8, ratio6_1, true);
motor intake = motor(PORT9, ratio6_1, false);
motor roller = motor(PORT10, ratio36_1, false);
line disc1 = line(Brain.ThreeWirePort.C);
line disc2 = line(Brain.ThreeWirePort.D);
line disc3 = line(Brain.ThreeWirePort.E);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;
// define variables used for controlling motors based on controller inputs
bool Controller1UpDownButtonsControlMotorsStopped = true;
bool Controller1XBButtonsControlMotorsStopped = true;

// define a task that will handle monitoring inputs from Controller1
int rc_auto_loop_function_Controller1() {
  // process the controller input every 20 milliseconds
  // update the motors based on the input values
  while(true) {
    if(RemoteControlCodeEnabled) {
      // check the ButtonUp/ButtonDown status to control LeftMotor1
      if (Controller1.ButtonUp.pressing()) {
        LeftMotor1.spin(forward);
        Controller1UpDownButtonsControlMotorsStopped = false;
      } else if (Controller1.ButtonDown.pressing()) {
        LeftMotor1.spin(reverse);
        Controller1UpDownButtonsControlMotorsStopped = false;
      } else if (!Controller1UpDownButtonsControlMotorsStopped) {
        LeftMotor1.stop();
        // set the toggle so that we don't constantly tell the motor to stop when the buttons are released
        Controller1UpDownButtonsControlMotorsStopped = true;
      }
      // check the ButtonX/ButtonB status to control RightMotor1
      if (Controller1.ButtonX.pressing()) {
        RightMotor1.spin(forward);
        Controller1XBButtonsControlMotorsStopped = false;
      } else if (Controller1.ButtonB.pressing()) {
        RightMotor1.spin(reverse);
        Controller1XBButtonsControlMotorsStopped = false;
      } else if (!Controller1XBButtonsControlMotorsStopped) {
        RightMotor1.stop();
        // set the toggle so that we don't constantly tell the motor to stop when the buttons are released
        Controller1XBButtonsControlMotorsStopped = true;
      }
    }
    // wait before repeating the process
    wait(20, msec);
  }
  return 0;
}

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  task rc_auto_loop_task_Controller1(rc_auto_loop_function_Controller1);
}