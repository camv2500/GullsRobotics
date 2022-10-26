#include "robot-config.h"
#include "vex.h"

void moveAll(double power){
    leftMotor1.spin(forward,power,pct);
    //leftMotor2.spin(forward,power,pct);
    //leftMotor3.spin(forward,power,pct);
    rightMotor1.spin(forward,power,pct);
    //rightMotor2.spin(forward,power,pct);
    //rightMotor3.spin(forward,power,pct);

}

void exitAutonInformation(double error, double derivative){
    Brain.Screen.print(error);
    Brain.Screen.print(" ");
    Brain.Screen.print(derivative);
    Brain.Screen.newLine();
    Brain.Screen.print("Leaving Auton");
    leftMotor1.spin(forward,0,pct);
    rightMotor1.spin(forward,0,pct);
}

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

//two setpoints for each side of the motors, left and right, which as of now is only two motors
//this has led to the kp and kd being slightly out of tune for some reason and the setpoints seemed to increase by 50%
//the reason for two is that in theory with two setpoints we can set the values seperately and thus allow turns by setting
//one motor to positive and one to negative to turn. corey says turning the robots into a unit circle would help
//my current line of thinking is that we should have one setpoint, and when we arrive at the setpoint we could have the second
//double be the raidus of the turn required, making sure the heading of the robot is in the correct after going the distance
//eventually we'll have it turn while it is moving the distance but this should be less complicated
void PDLoop(double setpoint, double turningSetPoint = 0){
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

  leftMotor1.setPosition(0,degrees);
  rightMotor1.setPosition(0,degrees);

  while (fabs(error) >= 1)
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
  exitAutonInformation(error, derivative);

}