#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor leftMotor = motor(PORT3, ratio18_1, false);
motor rightMotor = motor(PORT8, ratio18_1, false);
bumper UP = bumper(Brain.ThreeWirePort.A);
bumper select = bumper(Brain.ThreeWirePort.B);
bumper DOWN = bumper(Brain.ThreeWirePort.C);

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