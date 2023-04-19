#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor lMotor1 = motor(PORT8, ratio18_1, true);
motor lMotor2 = motor(PORT9, ratio18_1, true);
motor lMotor3 = motor(PORT10, ratio18_1, true);
motor rMotor1 = motor(PORT11, ratio18_1, false);
motor rMotor2 = motor(PORT6, ratio18_1, false);
motor rMotor3 = motor(PORT13, ratio18_1, false);
controller Controller1 = controller(primary);
motor intakeMotor = motor(PORT15, ratio18_1, true);
motor intakeMotor2 = motor(PORT7, ratio18_1, false);
motor FlywheelMotor = motor(PORT20, ratio18_1, false);
motor rollerMotor = motor(PORT1, ratio18_1, false);
digital_out indexer1 = digital_out(Brain.ThreeWirePort.A);
digital_out endGame = digital_out(Brain.ThreeWirePort.B);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}