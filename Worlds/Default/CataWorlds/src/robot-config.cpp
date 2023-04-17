#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor lMotor1 = motor(PORT10, ratio6_1, false);
motor lMotor2 = motor(PORT9, ratio6_1, false);
motor lMotor3 = motor(PORT8, ratio6_1, false);
motor lMotor4 = motor(PORT7, ratio6_1, false);
motor rMotor1 = motor(PORT6, ratio6_1, true);
motor rMotor2 = motor(PORT4, ratio6_1, true);
motor rMotor3 = motor(PORT3, ratio6_1, true);
motor rMotor4 = motor(PORT2, ratio6_1, true);
motor cataMotor = motor(PORT1, ratio36_1, false);
motor intakeRollerMotor = motor(PORT19, ratio6_1, false);
digital_out endGame = digital_out(Brain.ThreeWirePort.A);
controller Controller1 = controller(primary);
digital_out autonPiston = digital_out(Brain.ThreeWirePort.B);

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