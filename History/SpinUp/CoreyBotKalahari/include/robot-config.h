using namespace vex;

extern brain Brain;

// VEXcode devices
extern motor dL1;
extern motor dL2;
extern motor dL3;
extern motor dL4;
extern motor dR1;
extern motor dR2;
extern motor dR3;
extern motor dR4;
extern motor rlr;
extern controller Controller1;
extern digital_out mag;
extern motor fw1;
extern motor fw2;
extern digital_out indx;
extern motor itk;
extern digital_out endG;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );