/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// dL1                  motor         13              
// dL2                  motor         14              
// dL3                  motor         15              
// dL4                  motor         16              
// dR1                  motor         17              
// dR2                  motor         18              
// dR3                  motor         19              
// dR4                  motor         20              
// rlr                  motor         2               
// Controller1          controller                    
// mag                  digital_out   A               
// fw1                  motor         11              
// fw2                  motor         12              
// indx                 digital_out   B               
// itk                  motor         1               
// endG                 digital_out   C               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here

/*---------------------------------------------------------------------------
fw1: port11 600, rev
fw2: port12 600
dL1: port13 600, rev
dL2: port14 600, rev
dL3: port15 600, rev
dL4: port16 600, rev
dR1: port17 600
dR2: port18 600 
dR3: port19 600
dR4: port20 600
itk: portX 600
rlr: portX 600
mag: portA
indx: portB
endG: portC

---------------------------------------------------------------------------*/

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  while (1) {

    /*Controls:
    Axis 3: Left Drive
    Axis 2: Right Drive
    L1: Rotate Roller
    L2: Intake in, set mag down and indexer retracted
    R1: Hold to spin up flywheel and bring mag up (when released flywheel slows down and mag lowers)
    R2: Single press - triple piston actuation
    ArrowRight: Intake out
    Y: Endgame deploy*/

    //Drive motor control---------------------------------------------
    
    dL1.spin(fwd, Controller1.Axis2.value(), vex::velocityUnits::pct);
    dL2.spin(fwd, Controller1.Axis2.value(), vex::velocityUnits::pct);
    dL3.spin(fwd, Controller1.Axis2.value(), vex::velocityUnits::pct);
    dL4.spin(fwd, Controller1.Axis2.value(), vex::velocityUnits::pct);
    dR1.spin(fwd, Controller1.Axis3.value(), vex::velocityUnits::pct);
    dR2.spin(fwd, Controller1.Axis3.value(), vex::velocityUnits::pct);
    dR3.spin(fwd, Controller1.Axis3.value(), vex::velocityUnits::pct);
    dR4.spin(fwd, Controller1.Axis3.value(), vex::velocityUnits::pct);
    //----------------------------------------------------------------

    //Intake Control-----------------------------
    if(Controller1.ButtonL2.pressing()){
      mag.set(true);
      indx.set(false);
      itk.spin(fwd, 100, pct);
    }else if(Controller1.ButtonRight.pressing()){
      itk.spin(reverse, 100, pct);
    }else
      itk.stop(brakeType::coast);
    //-------------------------------------------

    //Roller Control-----------------------------------------------------------------
    if(Controller1.ButtonL1.pressing()){
      rlr.startRotateFor(100, vex::rotationUnits::raw, 100, vex::velocityUnits::pct);
    }
    //-------------------------------------------------------------------------------

    //Flywheel Control-----------------------------------------------------------
    if(Controller1.ButtonR1.pressing()){
      mag.set(false);
      fw1.spin(reverse, 100, pct);
      fw2.spin(reverse, 100, pct);
      if(Controller1.ButtonR2.pressing())
      {
        fw1.spin(reverse, 100, pct);
        fw2.spin(reverse, 100, pct);
        indx.set(true);
        vex::task::sleep(500);
        indx.set(false);
        vex::task::sleep(500);
      }
    }else if(Controller1.ButtonR1.pressing() && Controller1.ButtonR2.pressing()){
      indx.set(true);
      vex::task::sleep(1000);
      indx.set(false);
      wait(1000, msec);
      indx.set(true);
      wait(1000, msec);
      indx.set(false);
      wait(1000, msec);
      indx.set(true);
      wait(1000, msec);
      indx.set(false);
    }else{
      fw1.stop(brakeType::coast);
      fw2.stop(brakeType::coast);
    }
    //---------------------------------------------------------------------------

    //Endgame deploy----------------------
    if(Controller1.ButtonY.pressing()){
      endG.set(true);
    }
    //-----------------------------------
    
    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
