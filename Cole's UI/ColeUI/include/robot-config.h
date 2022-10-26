using namespace vex;

extern brain Brain;

// VEXcode devices
extern bumper select;
extern bumper UP;
extern bumper DOWN;
extern controller Controller1;
extern motor leftMotor;
extern motor rightMotor;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );