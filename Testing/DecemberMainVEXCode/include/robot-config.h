using namespace vex;

extern brain Brain;

// VEXcode devices
extern motor lMotor1;
extern motor lMotor2;
extern motor lMotor3;
extern motor rMotor1;
extern motor rMotor2;
extern motor rMotor3;
extern motor cataMotor;
extern motor intakeRollerMotor;
extern controller Controller1;
extern limit cataLimit;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );