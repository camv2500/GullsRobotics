#include "vex.h"
#include "robot-config.h"

double mLSpeed = 0;
double mRSpeed = 0;
double mAllSpeedB = 0;
//double mAllAvg = 0;



void mBLeft(){
    Ml1.spin(vex::forward, mLSpeed, pct);
    Ml2.spin(vex::forward, mLSpeed, pct);
    Ml3.spin(vex::forward, mLSpeed, pct);
}

void setmLSpeed(double mL) {
  mLSpeed = mL;
}

double getmLSpeed() {
  return mLSpeed;
}





//All Motors

void mAll(){
    Ml1.spin(vex::forward, mAllSpeedB, pct);
    Mr1.spin(vex::forward, mAllSpeedB, pct);
    Ml2.spin(vex::forward, mAllSpeedB, pct);
    Mr2.spin(vex::forward, mAllSpeedB, pct);
    Ml3.spin(vex::forward, mAllSpeedB, pct);
    Mr3.spin(vex::forward, mAllSpeedB, pct);
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
    Mr1.spin(vex::forward, mRSpeed, pct);
    Mr2.spin(vex::forward, mRSpeed, pct);
    Mr3.spin(vex::forward, mRSpeed, pct);  
}
void setmRSpeed(double mR) {
  mRSpeed = mR;
}

double getmRSpeed() {
  return mRSpeed;
}



//drive motor encoder reset
void encoderReset(){
  Mr1.setPosition(0,rev);
  Mr2.setPosition(0,rev);
  Mr3.setPosition(0,rev);
  Ml1.setPosition(0,rev);
  Ml2.setPosition(0,rev);
  Ml3.setPosition(0,rev);
}


//Catapult Shooting position


