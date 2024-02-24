#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor rightMiddle = motor(PORT9, ratio6_1, false);
motor rightFront = motor(PORT10, ratio6_1, true);
motor rightRear = motor(PORT8, ratio6_1, false);
motor leftFront = motor(PORT1, ratio6_1, false);
motor leftMiddle = motor(PORT2, ratio6_1, true);
motor leftRear = motor(PORT3, ratio6_1, true);
controller Controller1 = controller(primary);
motor Catapult = motor(PORT21, ratio36_1, false);
limit cataLimit = limit(Brain.ThreeWirePort.A);
digital_out liftPistons = digital_out(Brain.ThreeWirePort.F);
digital_out intakePistons = digital_out(Brain.ThreeWirePort.C);
motor Intake = motor(PORT5, ratio18_1, false);
motor rightRaised = motor(PORT6, ratio6_1, true);
motor leftRaised = motor(PORT4, ratio6_1, false);

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