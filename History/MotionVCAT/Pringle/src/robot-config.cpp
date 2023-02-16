#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor lMotor1 = motor(PORT11, ratio18_1, false);
motor lMotor2 = motor(PORT12, ratio18_1, false);
controller Controller1 = controller(primary);
motor FlyWheel1 = motor(PORT9, ratio6_1, true);
motor FlyWheel2 = motor(PORT10, ratio6_1, false);
motor rMotor1 = motor(PORT15, ratio18_1, true);
motor rMotor2 = motor(PORT16, ratio18_1, true);
motor rMotor3 = motor(PORT17, ratio18_1, true);
motor rMotor4 = motor(PORT19, ratio18_1, true);
motor lMotor3 = motor(PORT13, ratio18_1, false);
motor lMotor4 = motor(PORT14, ratio18_1, false);
motor intakeMotor = motor(PORT2, ratio18_1, false);
digital_out magLifter = digital_out(Brain.ThreeWirePort.A);
digital_out indexer1 = digital_out(Brain.ThreeWirePort.B);
digital_out endGame = digital_out(Brain.ThreeWirePort.C);
motor rollerMotor = motor(PORT21, ratio18_1, false);

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