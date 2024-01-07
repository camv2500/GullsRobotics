using namespace vex;

extern brain Brain;

// VEXcode devices
extern motor rightMiddle;
extern motor rightFront;
extern motor rightRear;
extern motor leftFront;
extern motor leftMiddle;
extern motor leftRear;
extern controller Controller1;
extern motor Catapult;
extern limit cataLimit;
extern digital_out liftPistons;
extern digital_out intakePistons;
extern motor Intake;
extern motor rightRaised;
extern motor leftRaised;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );