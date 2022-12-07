using namespace vex;

extern brain Brain;

// VEXcode devices
extern motor LeftMotor1;
extern motor RightMotor1;
extern controller Controller1;
extern motor FlyWheel1;
extern motor FlyWheel2;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );