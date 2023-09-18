#include "main.h"
#include "robot-config.h"
#include "DriverControl.h"
#include "AutonFunctions.h"
#include "Autonomous.h"

using namespace pros;

int driveDistance;



/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

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
void autonomous() {}


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
void opcontrol() {
	// Controller master(pros::E_CONTROLLER_MASTER);
	// Motor left_mtr(1);
	// Motor right_mtr(2);

	// while (true) {
	// 	lcd::print(0, "%d %d %d", (lcd::read_buttons() & LCD_BTN_LEFT) >> 2,
	// 	                 (lcd::read_buttons() & LCD_BTN_CENTER) >> 1,
	// 	                 (lcd::read_buttons() & LCD_BTN_RIGHT) >> 0);
	// 	int left = master.get_analog(ANALOG_LEFT_Y);
	// 	int right = master.get_analog(ANALOG_RIGHT_Y);

	// 	left_mtr = left;
	// 	right_mtr = right;

	// 	delay(20);
	// }

	// driverControl();

	gpsPosition(0, 0, false);
	
}

int goToPosition(float x, float y, int motorSpeed, float distancePerCheck, bool backwards, bool useLateral) {
  bool travelDirection = backwards; // Booleans for moving forward and backwards or using lateralPID
  bool usingLateral = useLateral;
  int speed = motorSpeed;
  float checkingDistance = distancePerCheck;
  
  float currentX = gpsSensor.xPosition(); // Taking our current x and y position
  float currentY = gpsSensor.yPosition();
  //generatePosition(&currentX, &currentY);

  //Checks to see if we are already at our target position
  if((fabs(currentX - x) < 200 && fabs(currentY - y) < 200)) {
    return 1;
  }

  gpsPosition(x , y, travelDirection);

  float startingX = gpsSensor.xPosition();// Taking our starting X position
  float startingY = gpsSensor.yPosition();
  
  //generatePosition(&startingX, &startingY);

  float deltaX; // Declaring change in x, change in y, and distance
  float deltaY; 
  float distanceTraveled;  

  float inches; // paramter to pass into lateralPID

  // Finding the distance we need to travel in inches for lateralPID
  inches = (sqrt(fabs((x - startingX)*(x-startingX)) + fabs((y - startingY)*(y-startingY)))) * (0.03937007874); 

  if(usingLateral) { // Checks if we are using lateral or not
    LateralPID(inches);
  }
  else { // If not using lateral, checks what direction we are going in. false is forwards, true is backwards
    if(!travelDirection) {
      leftDrive.spin(fwd, speed, pct);
      rightDrive.spin(fwd, speed, pct);
    }
    else {
      leftDrive.spin(reverse, speed, pct);
      rightDrive.spin(reverse, speed, pct);
    } 
  }
  
  // Loop to check our current position. If we get in range we will stop
  while(!(fabs(currentX - x) < 100 && fabs(currentY - y) < 100)) {
    deltaX = fabs(startingX - currentX); // Taking our change in x and change in y
    deltaY = fabs(startingY - currentY);

    distanceTraveled = sqrt((deltaX * deltaX) + (deltaY * deltaY)); // Checks how far its traveled
    if(distanceTraveled > checkingDistance) { // Readjusting after given distance
      startingX = gpsSensor.xPosition();
      startingY = gpsSensor.yPosition();
      //generatePosition(&startingX, &startingY);

      //leftDrive.stop(hold);
      //rightDrive.stop(hold);

      goToPosition(x, y, speed, checkingDistance, travelDirection, usingLateral); // Recursively calls function

    }

    currentX = gpsSensor.xPosition();
    currentY = gpsSensor.yPosition();
    lcd::setCursor(4, 1);
    lcd::print("Current X: %0.2lf", currentX);
    
    lcd::setCursor(5, 1);
    lcd::print("Current Y: %0.2lf", currentY);
  }
  leftDrive.stop(hold);
  rightDrive.stop(hold);
  return 1;
}

int faceHeading(float targetHeading) {
    lcd::print(0, "This ran");
    float targetAngle = targetHeading;
    float currentAngle = gpsSensor.heading();
    float turnAngle;

    if(currentAngle < 0) {
      currentAngle = 360 + currentAngle;
    }
    turnAngle = targetAngle - currentAngle;

    if(turnAngle > 180) {
      turnAngle = turnAngle - 360;
    }
    //turnAngle = turnAngle * -1;
    while(true){
      if(fabs(currentAngle - targetHeading) < 10){
        break;
      }
      if(turnAngle < 0) {
        leftDrive.spin(reverse, 10, pct);
        rightDrive.spin(fwd, 10, pct);
      }
      else {
        leftDrive.spin(fwd, 10, pct);
        rightDrive.spin(reverse, 10, pct);
      }
    }
    TurnPID(turnAngle);
    return 1;
}

void gpsPosition(float x, float y, bool backwards) {
    // lcd::setCursor(6, 1);
    lcd::print(6, "Starting X: %0.2lf", gpsSensor.xPosition());

    // lcd::setCursor(7, 1);
    lcd::print(7, "Starting Y: %0.2lf", gpsSensor.yPosition());

    bool travelDirection = backwards;
    // Orient the drivetrain's heading with the gpsSensor heading
    // gpsSensor.setHeading(gpsSensor.heading(), degrees);
	gpsSensor.setHeading(gpsSensor.heading());
    
    // Print the starting position of the robot
    // gpsPrint();
    
    // Store the current position of the robot
    float startingX = gpsSensor.xPosition();
    float startingY = gpsSensor.yPosition();

    // Store the target ending position of the robot
    float endingX = x;
    float endingY = y;

    // Get the initial angle before the turn angle
    float initialAngle = gpsSensor.heading();

    // Implement atan2 to calculate the heading that the robot needs to
    // turn to in order to drive towards the ending position
    float deltaX = endingX - startingX;
    float deltaY = endingY - startingY;

    // lcd::setCursor(1, 1);
    lcd::print(1, "Delta X: %0.2lf", deltaX);

    // lcd::setCursor(2, 1);
    lcd::print(2, "Delta Y: %0.2lf", deltaY);

    float turnAngle = atan((deltaX) / (deltaY)) * 180 / M_PI;
    // lcd::print("Angle: %f", turnAngle); // Prints out turn angle
    // lcd::newLine();

    // Finding the angle
    if (endingY - startingY < 0) {
      turnAngle = turnAngle + 180;
    }

    // Making the angle not negative
    if (initialAngle > 180) {
      initialAngle = initialAngle - 360;
    }

    turnAngle = turnAngle - initialAngle; // Find the turn
    // lcd::setCursor(3, 1);
    lcd::print(3, "%0.2lf", turnAngle);

    // if (runIntake) {
    //   turnAngle = turnAngle + 180;
    // }

    // Take the shortest turn
    if (turnAngle > 180) {
      turnAngle = turnAngle - 360;
    }
    
    // lcd::print("Angle: %f", turnAngle);
    // lcd::newLine();

    // Turn the robot to face the ending position
    if(!travelDirection) {
     TurnPID(turnAngle); 
     printf("\n");
     printf("Turn Angle facing front: %0.2lf\n", turnAngle);
    }
    else {
      if(turnAngle < 0) {
        turnAngle = turnAngle + 180;
      }
      else {
        turnAngle = turnAngle - 180;
      }
      printf("\n");
      printf("Turn Angle facing back: %0.2lf\n", turnAngle);
      TurnPID(turnAngle);
    }

   
     

    // Calculate the drive distance needed, then drive towards the target position
    driveDistance = sqrt(((endingX - startingX) * (endingX - startingX)) + ((endingY - startingY) * (endingY - startingY)));
    // lcd::print("Distance: %f", driveDistance);
    // lcd::newLine();
    
    // Print the ending position of the robot
    // gpsPrint();
    
}