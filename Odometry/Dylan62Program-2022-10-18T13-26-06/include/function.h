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