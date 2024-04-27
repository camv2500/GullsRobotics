using namespace vex;

extern brain Brain;

// VEXcode devices
extern motor lMotor1;
extern motor lMotor2;
extern motor lMotor3;
extern motor rMotor1;
extern motor rMotor2;
extern motor rMotor3;
extern motor intakeRollerMotor;
extern controller Controller1;
extern digital_out intakeFlip;
extern digital_out wings;
extern motor rMotor4;
extern motor lMotor4;
extern motor passThru;
extern distance ballDetector;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );