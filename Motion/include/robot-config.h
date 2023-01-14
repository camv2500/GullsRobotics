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

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );