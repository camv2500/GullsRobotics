using namespace vex;

extern brain Brain;

// VEXcode devices
extern motor Mr1;
extern motor Mr2;
extern motor Mr3;
extern motor Ml1;
extern motor Ml2;
extern motor Ml3;
extern controller Controller1;
extern motor Catapult;
extern limit cataLimit;
extern digital_out liftPistons;
extern digital_out intakePistons;
extern motor Intake;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );