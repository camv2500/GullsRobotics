using namespace vex;

extern brain Brain;

// VEXcode devices
extern motor lMotor1;
extern motor lMotor2;
extern controller Controller1;
extern motor FlyWheel1;
extern motor FlyWheel2;
extern motor rMotor1;
extern motor rMotor2;
extern motor rMotor3;
extern motor rMotor4;
extern motor lMotor3;
extern motor lMotor4;
extern motor intakeMotor;
extern digital_out magLifter;
extern digital_out indexer1;
extern digital_out endGame;
extern motor rollerMotor;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );