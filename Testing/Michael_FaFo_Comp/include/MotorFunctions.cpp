#include "vex.h"
#include "MotorDefine.h"
#include "math.h"
using namespace vex;

double kPL =0;
double kIL =0;
double kDL =0;
double targetL=0;
double derivativeL = 0;
double errorL = 0;
double previous_errorL = 0;
double intergalL = 0;
double mLAvg = 0;


double kPR =0;
double kIR =0;
double kDR =0;
double targetR=0;
double derivativeR = 0;
double errorR = 0;
double previous_errorR = 0;
double intergalR = 0;
double mRAvg = 0;


double kPA =0;
double kIA =0;
double kDA =0;
double targetA=0;
double derivativeA = 0;
double errorA = 0;
double previous_errorA = 0;
double intergalA = 0;
double mAllAvg = 0;

int cataPosition =0;


void pidCalcLBank( double kpl, double kil, double kdl,double TargetL){
  kPL=kpl;
  kIL=kil;
  kDL=kdl;
  targetL=TargetL;
  mLAvg = (leftFront.rotation(rev) + leftMiddle.rotation(rev) + leftRear.rotation(rev)+ leftRaised.rotation(rev))/4;
 errorL = targetL - mLAvg;
 /*intergalL += errorL;

  if (errorL==0){
  intergalL = 0;
}

  if (fabs(errorL)>100){
  intergalL =0;
}


derivativeL = errorL- previous_errorL; 
previous_errorL = errorL;*/
mLSpeed = (kPL*errorL);//+(kIL*intergalL)+(kDL*derivativeL);
setmLSpeed(mLSpeed);
}

void pidCalcRBank(double kpr, double kir, double kdr, double TargetR){
  kPR=kpr;
  kIR=kir;
  kDR=kdr; 
  targetR=TargetR;
  mRAvg = (rightFront.rotation(rev) + rightMiddle.rotation(rev) + rightRear.rotation(rev)+ rightRaised.rotation(rev))/4;
  

 errorR = targetR - mRAvg;
 
 /*intergalR += errorR;

if (errorR==0){
  intergalR = 0;
}

if (fabs(errorR)>100){
  intergalR =0;
}


derivativeR = errorR- previous_errorR; 
previous_errorR = errorR;*/
mRSpeed = (kPR*errorR);//+(kIR*intergalR)+(kDR*derivativeR);
setmRSpeed(mRSpeed);
}



//all Motor PID

void pidCalcAll(double kpa, double kia, double kda, double TargetA){
  kPA=kpa;
  kIA=kia;
  kDA=kda; 
  targetA=TargetA;
  mAllAvg = (rightFront.rotation(rev) + rightMiddle.rotation(rev) + rightRear.rotation(rev)+ rightRaised.rotation(rev)+leftFront.rotation(rev) + leftMiddle.rotation(rev) + leftRear.rotation(rev)+ leftRaised.rotation(rev))/8;

 errorA = targetA - mAllAvg;
 
 intergalA += errorA;

if (errorA==0){
  intergalA = 0;
}

if (fabs(errorA)>100){
  intergalA =0;
}


previous_errorA = errorA;
derivativeA = errorA- previous_errorA; 

//previous_errorA = errorA;

mAllSpeedB = (kPA*errorA) +(kIA*intergalA) + ( kDA*derivativeA);
setmAllSpeed(mAllSpeedB);
wait (10,msec);
}

void firePosition(){
  cataPosition = cataLimit.pressing();

}


