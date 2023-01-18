#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor dL1 = motor(PORT20, ratio6_1, true);
motor dL2 = motor(PORT19, ratio6_1, true);
motor dL3 = motor(PORT15, ratio6_1, true);
motor dL4 = motor(PORT17, ratio6_1, true);
motor dR1 = motor(PORT12, ratio6_1, false);
motor dR2 = motor(PORT11, ratio6_1, false);
motor dR3 = motor(PORT13, ratio6_1, false);
motor dR4 = motor(PORT14, ratio6_1, false);
motor rlr = motor(PORT16, ratio36_1, false);
controller Controller1 = controller(primary);
digital_out mag = digital_out(Brain.ThreeWirePort.A);
motor fw1 = motor(PORT1, ratio6_1, true);
motor fw2 = motor(PORT2, ratio6_1, false);
digital_out indx = digital_out(Brain.ThreeWirePort.B);
motor itk = motor(PORT3, ratio6_1, false);
digital_out endG = digital_out(Brain.ThreeWirePort.C);

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