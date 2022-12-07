#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor LeftMotor1 = motor(PORT14, ratio18_1, false);
motor RightMotor1 = motor(PORT13, ratio18_1, true);
controller Controller1 = controller(primary);
motor FlyWheel1 = motor(PORT11, ratio6_1, false);
motor FlyWheel2 = motor(PORT12, ratio6_1, true);

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