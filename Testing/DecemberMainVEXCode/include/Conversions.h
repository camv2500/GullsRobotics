#include <math.h>

//convert degrees to inches
double ConvertDegreesToInches(double setDegrees, double turnDiameter = 12.17) {
  double requiredInches = setDegrees / 360.0 * M_PI * turnDiameter;
  return requiredInches;
}

//convert the inches to revolutions
double ConvertInchesToRevolutions(double requiredInches, double circum = 3.86) {
  double circumferenceOfWheel = circum * M_PI;
  double outputRat = 3.0/5.0;
  double requiredRevolutions = (requiredInches / circumferenceOfWheel) * outputRat * 360.0;
  return requiredRevolutions;
}

//convert radians to degrees
double ConvertRadiansToDegrees(double radian) {
  radian = radian * (180.0 / M_PI);
  return radian;
}

//formula for how long of a wait between movements
double CalculateWaitTimeMove(double n) {
  n = 0.05 * n; n += 0.75; return n;
}

//formula for how long of a wait between rotations to enable quick speed but ensure completion of task
double CalculateWaitTimeRotate(double n) {
  n = 0.005 * n; n += 0.75; return n;
}

double controlCurve(double controllerPos){
  //Slow curve
  return (exp(-14.6/10)+exp((fabs(controllerPos)-100)/10)*(1-exp(-14.6/10)))*controllerPos;
}