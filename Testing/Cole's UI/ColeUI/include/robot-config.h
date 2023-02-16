using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller Controller1;
extern motor leftMotor;
extern motor rightMotor;
extern bumper UP;
extern bumper select;
extern bumper DOWN;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );