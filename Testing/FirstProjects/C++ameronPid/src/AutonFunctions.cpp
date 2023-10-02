#include "robot-config.h"
#include "AutonFunctions.h"
#include "DriverControl.h"

using namespace pros;

const double Pi(3.14159265358979);

//convert the inches to revolutions
double ConvertInchesToRevolutions(double requiredInches, double circum) {
	//the circumference of the wheel fluxuates slightly due to the rubber nature which is why it is a value that needs to be tuned
  double circumferenceOfWheel = circum * Pi;
	//the output ratio is due to the gear ratio on the bot being 3 to 5. not sure if this will be needed on a new bot
  double outputRat = 3.0/5.0;
	//the forumal of converting inches to revolutions based on the info we have gathered / tuned
  double requiredRevolutions = (requiredInches / circumferenceOfWheel) * outputRat * 360.0;
  return requiredRevolutions;
}

//spin the motors for pid. enough said
void SpinMotors(double power, bool isTurning) {
  leftMotorGroup.move(power);
  rightMotorGroup.move(power);
}

//these are the most important variables!! they control how the pid is defined and how much each part impacts
//the program. the hardest pard of PID is tuning these three variables and it will take time. can only
//be done effectively when the robot is done or almost done as to not waste time
double kP = 0.1775, kI = 0, kD = 0.01775;
double integral = 0, derivative = 0, error = 0, power = 0, prevError = 0;

//the distance is in revolutions, the encoders should only be reset on first use
void runPID(double pidSetDegrees, bool resetEncoders) {
  /*//reset the encoders when a new pid call occurs
  //commented out for right now due to being unnecessary for the beginning tests
  if (resetEncoders) {
    resetEncoders = false;
    ResetEncoders();
    integral = 0;
    derivative = 0;
  }*/

	//make sure the program isnt trying to waste resources by saying it needs to move nowhere
  if (pidSetDegrees != 0) {
	//get the current motor encoders and average them all together
    double lSensor = (lmotor1.get_position() + lmotor2.get_position()) / 2;
    double rSensor = (rmotor1.get_position() + rmotor2.get_position()) / 2;
    double sensorValue = (lSensor + rSensor) / 2;
	//error, which uses kP, is Goal Distance - Distance Traveled
    error = pidSetDegrees - sensorValue;

	//integral, using kI, is the total of how far left we have to go in each iteration
	//easily the most finicky of the group and arguably not needed for our purposes
    integral = integral + error;
    if (fabs(integral) > 5000) {integral = 5000;}

	//derivative, using kD, is the change in error from this set to the previous set, and is 
	//used to make sure the program is moving at a more consistent rate
    derivative = error - prevError;
    prevError = error;

	//the total power given to the motors is the combination of PID and is sent as a percent as of now
	//for example a power of 5 would mean the motors need to go at 5% of full force
    power = error * kP + integral * kI + derivative * kD;

	//commented out for now but this is to limit jerkiness of the robot by limiting the speed. in a perfect
	//world the pid will be tuned well enough that there is no jerkiness, but it can also be caused by a 
	//number of other issues, and as such it is typically just limited here.
    //if (power > 33.5) {power = 33.5;}
    //if (power < -33.5) {power = -33.5;}
  
    SpinMotors(power);
  }
  else {
    SpinMotors(0);
  }
}

 double controlCurve(double conP){
  //Slow curve
  return (exp(-14.6/10)+exp((fabs(conP)-100)/10)*(1-exp(-14.6/10)))*conP;
}