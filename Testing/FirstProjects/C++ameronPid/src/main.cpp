#include "main.h"
#include "robot-config.h"
// #include "AutonFunctions.h"
// #include "DriverControl.h"
// #include "autonomous.h"

using namespace pros;

const double M_PI(3.14159265358979);

//convert the inches to revolutions
double ConvertInchesToRevolutions(double requiredInches, double circum = 3.86) {
	//the circumference of the wheel fluxuates slightly due to the rubber nature which is why it is a value that needs to be tuned
  double circumferenceOfWheel = circum * M_PI;
	//the output ratio is due to the gear ratio on the bot being 3 to 5. not sure if this will be needed on a new bot
  double outputRat = 3.0/5.0;
	//the forumal of converting inches to revolutions based on the info we have gathered / tuned
  double requiredRevolutions = (requiredInches / circumferenceOfWheel) * outputRat * 360.0;
  return requiredRevolutions;
}

//spin the motors for pid. enough said
void SpinMotors(double power, bool isTurning = false) {
  leftMotorGroup.move(power);
  rightMotorGroup.move(power);
}

//these are the most important variables!! they control how the pid is defined and how much each part impacts
//the program. the hardest pard of PID is tuning these three variables and it will take time. can only
//be done effectively when the robot is done or almost done as to not waste time
double kP = 0.1775, kI = 0, kD = 0.01775;
double integral = 0, derivative = 0, error = 0, power = 0, prevError = 0;

//the distance is in revolutions, the encoders should only be reset on first use
void runPID(double pidSetDegrees, bool resetEncoders = false) {
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

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		lcd::set_text(2, "I was pressed!");
	} else {
		lcd::clear_line(2);
	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	lcd::initialize();
	lcd::set_text(1, "Hello PROS User!");

	lcd::register_btn1_cb(on_center_button);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
	//convert the inches to revolutions
	double revs = ConvertInchesToRevolutions(180);
	//print out the revolutions that it will be using on the robot
	lcd::print(1, "%f", revs);
	while(true) {
		//continuously run the pid function, but each time it runs it will use the updated motor encoders to
		//reflect how far the robot has actually moved
		runPID(revs);
	}
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */

 double controlCurve(double conP){
  //Slow curve
  return (exp(-14.6/10)+exp((fabs(conP)-100)/10)*(1-exp(-14.6/10)))*conP;
}

void opcontrol() {
	while (true) {
		double leftDrive = (Controller1.get_analog(ANALOG_RIGHT_Y) + Controller1.get_analog(ANALOG_RIGHT_X));
    	double rightDrive = (Controller1.get_analog(ANALOG_RIGHT_Y) - Controller1.get_analog(ANALOG_RIGHT_X));
		leftMotorGroup.move(leftDrive);
		rightMotorGroup.move(rightDrive);
		lcd::print(1, "%f", lmotor1.get_position());

		delay(10);
	}
}
