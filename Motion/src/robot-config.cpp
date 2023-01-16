#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor lMotor14 = motor(PORT14, ratio18_1, false);
motor lMotor13 = motor(PORT13, ratio18_1, false);
controller Controller1 = controller(primary);
motor FlyWheel1 = motor(PORT16, ratio6_1, false);
motor FlyWheel2 = motor(PORT15, ratio6_1, true);
motor rMotor17 = motor(PORT17, ratio18_1, true);
motor rMotor18 = motor(PORT18, ratio18_1, true);
motor rMotor19 = motor(PORT19, ratio18_1, true);
motor rMotor20 = motor(PORT20, ratio18_1, true);
motor lMotor11 = motor(PORT11, ratio18_1, false);
motor lMotor12 = motor(PORT12, ratio18_1, false);
motor intakeMotor = motor(PORT5, ratio18_1, false);
digital_out magLifter = digital_out(Brain.ThreeWirePort.A);
digital_out diskPusher1 = digital_out(Brain.ThreeWirePort.B);
digital_out endGame = digital_out(Brain.ThreeWirePort.C);
motor rollerMotor = motor(PORT1, ratio18_1, false);

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