

void moveAll(double power){
    leftMotor1.spin(forward,power,pct);
    rightMotor1.spin(forward,power,pct);

}

void exitAuton(){
    Brain.Screen.print(error);
    Brain.Screen.print(" ");
    Brain.Screen.print(derivative);
    Brain.Screen.newLine();
    Brain.Screen.print("Leaving Auton");
    leftMotor1.spin(forward,0,pct);
    rightMotor1.spin(forward,0,pct);
}