#include "vex.h"
#include "robot-config.h"

double mLSpeed = 0;
double mRSpeed = 0;
double mAllSpeedB = 0;
//double mAllAvg = 0;



void mBLeft(){
    leftFront.spin(vex::forward, mLSpeed, pct);
    leftMiddle.spin(vex::forward, mLSpeed, pct);
    leftRear.spin(vex::forward, mLSpeed, pct);
    leftRaised.spin(vex::forward, mLSpeed, pct);
}

void setmLSpeed(double mL) {
  mLSpeed = mL;
}

double getmLSpeed() {
  return mLSpeed;
}





//All Motors

void mAll(){
    leftFront.spin(vex::forward, mAllSpeedB, pct);
    leftMiddle.spin(vex::forward, mAllSpeedB, pct);
    leftRear.spin(vex::forward, mAllSpeedB, pct);
    leftRaised.spin(vex::forward, mAllSpeedB, pct);
    rightFront.spin(vex::forward, mAllSpeedB, pct);
    rightMiddle.spin(vex::forward, mAllSpeedB, pct);
    rightRear.spin(vex::forward, mAllSpeedB, pct);
    rightRaised.spin(vex::forward, mAllSpeedB, pct);
}

void setmAllSpeed(double mA) {
  mAllSpeedB = mA;
}

double getmAllSpeed() {
  return mAllSpeedB;
}

/*void avgEncoder(){
mAllAvg = (Ml1.rotation(rev) + Ml2.rotation(rev) + Ml3.rotation(rev)+Mr1.rotation(rev) + Mr2.rotation(rev) + Mr3.rotation(rev))/6;
}*/





void mBRight(){
    rightFront.spin(vex::forward, mRSpeed, pct);
    rightMiddle.spin(vex::forward, mRSpeed, pct);
    rightRear.spin(vex::forward, mRSpeed, pct); 
    rightRaised.spin(vex::forward, mRSpeed, pct);  
}
void setmRSpeed(double mR) {
  mRSpeed = mR;
}

double getmRSpeed() {
  return mRSpeed;
}



//drive motor encoder reset
void encoderReset(){
  leftFront.setPosition(0,rev);
  leftMiddle.setPosition(0,rev);
  leftRear.setPosition(0,rev);
  leftRaised.setPosition(0,rev);
  rightFront.setPosition(0,rev);
  rightMiddle.setPosition(0,rev);
  rightRear.setPosition(0,rev);
  rightRaised.setPosition(0,rev);
}


//Catapult Shooting position


