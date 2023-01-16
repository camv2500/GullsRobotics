using namespace vex;

extern brain Brain;

// VEXcode devices
extern motor lMotor14;
extern motor lMotor13;
extern controller Controller1;
extern motor FlyWheel1;
extern motor FlyWheel2;
extern motor rMotor17;
extern motor rMotor18;
extern motor rMotor19;
extern motor rMotor20;
extern motor lMotor11;
extern motor lMotor12;
extern motor intakeMotor;
extern digital_out magLifter;
extern digital_out diskPusher1;
extern digital_out endGame;
extern motor rollerMotor;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );