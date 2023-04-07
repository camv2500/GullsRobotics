#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor lMotor1 = motor(PORT1, ratio18_1, false);
motor lMotor2 = motor(PORT2, ratio18_1, false);
motor lMotor3 = motor(PORT3, ratio18_1, false);
motor lMotor4 = motor(PORT4, ratio18_1, false);
motor rMotor1 = motor(PORT5, ratio18_1, false);
motor rMotor2 = motor(PORT6, ratio18_1, false);
motor rMotor3 = motor(PORT7, ratio18_1, false);
motor rMotor4 = motor(PORT8, ratio18_1, false);

// VEXcode generated functions



/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}