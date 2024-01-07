#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor rightMiddle = motor(PORT19, ratio6_1, false);
motor rightFront = motor(PORT20, ratio6_1, false);
motor rightRear = motor(PORT18, ratio6_1, false);
motor leftFront = motor(PORT11, ratio6_1, true);
motor leftMiddle = motor(PORT12, ratio18_1, true);
motor leftRear = motor(PORT13, ratio6_1, true);
controller Controller1 = controller(primary);
motor Catapult = motor(PORT5, ratio36_1, false);
limit cataLimit = limit(Brain.ThreeWirePort.A);
digital_out liftPistons = digital_out(Brain.ThreeWirePort.F);
digital_out intakePistons = digital_out(Brain.ThreeWirePort.C);
motor Intake = motor(PORT10, ratio18_1, false);
motor rightRaised = motor(PORT17, ratio6_1, false);
motor leftRaised = motor(PORT14, ratio6_1, true);

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