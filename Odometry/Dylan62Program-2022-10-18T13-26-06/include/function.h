#include "robot-config.h"
#include "vex.h"

//a function that can be used to move all of the motors at once
void moveAll(double power){
    leftMotor1.spin(forward,power,pct);
    //leftMotor2.spin(forward,power,pct);
    //leftMotor3.spin(forward,power,pct);
    rightMotor1.spin(forward,power,pct);
    //rightMotor2.spin(forward,power,pct);
    //rightMotor3.spin(forward,power,pct);

}

//useful for debugging, this function will print any relevant values as needed
void exitAutonInformation(double error, double derivative){
    Brain.Screen.print(error);
    Brain.Screen.print(" ");
    Brain.Screen.print(derivative);
    Brain.Screen.newLine();
    Brain.Screen.print("Leaving Auton");
}

//returns the average of all the motos sensor values
double getSensorValue(){
  double sensorValueLeft,sensorValueRight,sensorValueTotal;
  sensorValueLeft = leftMotor1.position(degrees);
  sensorValueRight = rightMotor1.position(degrees);
  sensorValueTotal = sensorValueLeft + sensorValueRight / 2;
  return sensorValueTotal;
}

//for when we get more motors
double getSensorValueLeft() {
  return leftMotor1.position(degrees);
}

//for when we get more motors
double getSensorValueRight() {
  return rightMotor1.position(degrees);
}

//the pd loop for the robot, when given a specific distance the robot will travel that amount of distance. The setpoint is in
//degrees of the wheel. if the robot overshoots, it will return backwards slightly. already mostly tuned but will need to be refined to the final robot
void PDLoop(double setpoint, bool isTurning = false){
  //sensorValueTotal : average of left and right motor encoders
  //setpoint : the amount of rotations that we aim to move in degrees
  //derivative : holds the current amount of the derivative
  //prevError : holds the pervious error for calculation in the next cycle
  //power : holds the amount of power to give to the motor
  //error : hold the amount of distance left to go
  //kp : The kP value is used to tune our Porportional part of the PD controller
  //kD : the kD value is used to tune our Derivative part of the PD controller

  double derivative, prevError = 0;
  double power = 0, error = setpoint;
  double kP = 0.2485, kD = 0.119;

  //reset the position of the motors to make sure the distance is correct
  leftMotor1.setPosition(0,degrees);
  rightMotor1.setPosition(0,degrees);

  while (fabs(error) >= 1 && !isTurning)
  {
    //wheel diamtere 3.25
    //wheel circumference 10.21
    //per full rotation travels 6.126 inches

    error = setpoint - getSensorValue();
    
    derivative = error - prevError;
    prevError = error;

    power = error * kP + derivative * kD;
    
    leftMotor1.spin(forward,power,pct);
    rightMotor1.spin(forward,power,pct);
    wait(20,msec);
  }

  while (fabs(error) >= 1 && isTurning) 
  {
    error = setpoint - getSensorValue();
    
    derivative = error - prevError;
    prevError = error;

    power = error * kP + derivative * kD;
    
    leftMotor1.spin(forward,power,pct);
    rightMotor1.spin(reverse,power,pct);
    wait(20,msec);
  }

  exitAutonInformation(error, derivative);
}

//current function for turning the robot, converts the degrees given to inches required and sends it to the PDLoop
void turnRobot(double setDegrees)
{
  double trackWidth = 6; //guess for now
  double requiredDistance, rotationDegree;

  //this calculates how many inches is required to be moved each degree, can be simplified to the straight value when the trackWidth is known
  rotationDegree = trackWidth * 3.14 / 360;

  //this converts the degrees given into an amount of rotations that can be used for the PDLoop
  requiredDistance = rotationDegree * setDegrees / 2 / 0.02836;
  
  PDLoop(requiredDistance, true);
}