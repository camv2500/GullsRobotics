#include "robot-config.h"
#include "DriverControl.h"
#include "AutonFunctions.h"
#include "Autonomous.h"

using namespace pros;

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */

// variables

// int master_auton_timer();
// double master_auton_seconds = 0;
// void start_timer(double sec);

// extra colors

// Auton Routines
void competition_initialize() {}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///                                                            Red AUTONS                                                           ///
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void RedRedAuton() { // Auton 1: Goes for stack of three using SENSORS (RED SIDE)

    lcd::print(1, "Auton 1 (RED) Selected");
    // start_timer(44.5);

    // routine

    // chatGPTPID(-12);
    LateralPID(0, -12);
    
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  // Tasks to do after timer finishes
  
    // set_master_auton_enable();
    // set_perma_lock();
    // leftDrive.stop(coast);
    // rightDrive.stop(coast);

}

void Autonomous(int SelectedAuton) {

  switch(SelectedAuton) { // Selected auton determines which runs

    case 1:
      RedRedAuton();     // Uses sensors, goes for stack of three (RED SIDE)
    break;

    // case 2:
    //   RedBlueAuton();    // Uses sensors, loads and shoot preloads (RED SIDE)
    // break;

    // case 3:
    //   RedYellowAuton();  // Uses preset movements, goes for stack of three (RED SIDE)
    // break;

    // case 4:
    //   RedGreenAuton();   // Uses preset movements, loads and shoots preloads (RED SIDE)
    // break;

    // case 5:
    //   BlueRedAuton();    // Uses sensors, goes for stack of three (BLUE SIDE)
    // break;

    // case 6:
    //   BlueBlueAuton();   // Uses sensors, loads and shoot preloads (BLUE SIDE)
    // break;

    // case 7:
    //   BlueYellowAuton(); // Uses preset movements, goes for stack of three (BLUE SIDE)
    // break;

    // case 8:
    //   BlueGreenAuton();  // Uses preset movements, loads and shoots preloads (BLUE SIDE)
    // break;

    // case 9:
    //   OrangeRedAuton();  //
    // break;

    // case 10:
    //   OrangeBlueAuton(); //
    // break;

    // case 11:
    //   OrangeYellowAuton(); // 
    // break;

    // case 12:
    //   OrangeGreenAuton(); // 
    // break;

    // case 13:
    //   PurpleRedAuton();  // Programming Skills
    // break;

    // case 14:
    //   PurpleBlueAuton(); // 
    // break;

    // case 15:
    //   PurpleYellowAuton(); // 
    // break;

    // case 16:
    //   PurpleGreenAuton(); //  
    // break;

    default:
      // if there is non selected, do pre-auton screen again
      // PreAutonomous();
    break;

  }
}

int screenWidth  = 480;
int screenHeight = 230; // 272 pixels? 238

// int PreAutonomous() {

//   // Firstly, the menu selection is run to determine the red, blue, orange, and purple autons

//   ////////////////////////////////////////////////////////////////////////////////////////////////////
//   ///                           Draws Autonomous (2) options) Selection Menu                       ///
//   ////////////////////////////////////////////////////////////////////////////////////////////////////

//   lcd::clear();
//   screen::draw_rect(0, 0, screenWidth/2, screenHeight/2, red);//red (1)
//   screen::draw_rect(0, screenHeight/2, screenWidth/2, screenHeight/2, orange);//orange (3)
//   screen::draw_rect(screenWidth/2, 0, screenWidth/2, screenHeight/2, blue);//blue (2)
//   screen::draw_rect(screenWidth/2, screenHeight/2, screenWidth/2, screenHeight/2, purple);///purple (4)
// //   screen::setCursor(3, 8);
// //   screen::print("Red Team");
// //   screen::setCursor(3, 32);
// //   screen::print("Blue Team");
// //   screen::setCursor(9, 7);
// //   screen::print("Troubleshoot");
// //   screen::setCursor(9, 28);
// //   // lcd::print("Programing Ssssssskkkkkkkkiiiiiiiiillllllllllllllsssssss");
// //   lcd::print("Programing Skills");

//   ////////////////////////////////////////////////////////////////////////////////////////////////////
    
//   //This command blocks everything, but causes no issues because it is in the pre-auton, before the competition starts.
//   while(!lcd::pressing()  &&  !master.get_digital(E_CONTROLLER_DIGITAL_X)) {} // Waits until screen is pressed.

//   lcd::clear();
//   int XCoorSect = lcd::xPosition();
//   int YCoorSect = lcd::yPosition();

//   int SelectedAuton1 = 0;

//   if ((XCoorSect >= 0 && XCoorSect <= screenWidth/2) && (YCoorSect >= 0 && YCoorSect <= screenHeight/2)) SelectedAuton1 = 1; //red auton
//     else if ((XCoorSect >= 0 && XCoorSect <= screenWidth/2) && (YCoorSect >= screenHeight/2 && YCoorSect <= screenHeight)) SelectedAuton1 = 3; //orange auton

//     else if ((XCoorSect >= screenWidth/2 && XCoorSect <= screenWidth) && (YCoorSect >= 0 && YCoorSect <= screenHeight/2)) SelectedAuton1 = 2; //blue auton
//     else if ((XCoorSect >= screenWidth/2 && XCoorSect <= screenWidth) && (YCoorSect >= screenHeight/2 && YCoorSect <= screenHeight)) SelectedAuton1 = 4; //purple auton

//   lcd::Clear();
//   delay(20);

//   switch (SelectedAuton1) {

//     case 1:
//       screen::draw_rect(0, 0, screenWidth, screenHeight, red); // Red section
//     break;

//     case 2:
//       screen::draw_rect(0, 0, screenWidth, screenHeight, blue); // Blue section
//     break;

//     case 3:
//       screen::draw_rect(0, 0, screenWidth, screenHeight, orange); // Orange section
//     break;

//     case 4:
//       screen::draw_rect(0, 0, screenWidth, screenHeight, purple); // Purple section
//     break;

//     default:
//     break;

//   }

//   delay(500);
//   lcd::Clear();

//   // Then if yellow was pressed, a menu will show up for red and blue autons
//   // Otherwise, a menu will show up for orange and purple autons


//   ////////////////////////////////////////////////////////////////////////////////////////////////////
//   ///                           Draws Autonomous (4 options) Selection Menu                        ///
//   ////////////////////////////////////////////////////////////////////////////////////////////////////
//   if (SelectedAuton1 == 1) { // Red Button (RED SIDE AUTONS)
//   screen::draw_rect(0, 0, screenWidth/2, screenHeight/2, red);//red (1)
//   screen::draw_rect(0, screenHeight/2, screenWidth/2, screenHeight/2, yellow);//yellow (3)
//   screen::draw_rect(screenWidth/2, 0, screenWidth/2, screenHeight/2, blue);//blue (2)
//   screen::draw_rect(screenWidth/2, screenHeight/2, screenWidth/2, screenHeight/2, CSMGreen);///green (4)
//   lcd::setCursor(3, 9);
//   lcd::print("Auton 1");
//   lcd::setCursor(3, 33);
//   lcd::print("Auton 2");
//   lcd::setCursor(9, 9);
//   lcd::print("Auton 3");
//   lcd::setCursor(9, 33);
//   lcd::print("Auton 4");
//   }
//   if (SelectedAuton1 == 2) { // Blue Button (BLUE SIDE AUTONS)
//   screen::draw_rect(0, 0, screenWidth/2, screenHeight/2, red);//red (1)
//   screen::draw_rect(0, screenHeight/2, screenWidth/2, screenHeight/2, yellow);//yellow (3)
//   screen::draw_rect(screenWidth/2, 0, screenWidth/2, screenHeight/2, blue);//blue (2)
//   screen::draw_rect(screenWidth/2, screenHeight/2, screenWidth/2, screenHeight/2, CSMGreen);///green (4)
//   lcd::setCursor(3, 9);
//   lcd::print("Auton 1");
//   lcd::setCursor(3, 33);
//   lcd::print("Auton 2");
//   lcd::setCursor(9, 9);
//   lcd::print("Auton 3");
//   lcd::setCursor(9, 33);
//   lcd::print("Auton 4");
//   }
//   if (SelectedAuton1 == 3) { // Orange Button
//   screen::draw_rect(0, 0, screenWidth/2, screenHeight/2, red);//red (1)
//   screen::draw_rect(0, screenHeight/2, screenWidth/2, screenHeight/2, yellow);//yellow (3)
//   screen::draw_rect(screenWidth/2, 0, screenWidth/2, screenHeight/2, blue);//blue (2)
//   screen::draw_rect(screenWidth/2, screenHeight/2, screenWidth/2, screenHeight/2, CSMGreen);///green (4)
//   lcd::setCursor(3, 8);
//   lcd::print("Inertial");
//   lcd::setCursor(3, 35);
//   lcd::print("GPS");
//   lcd::setCursor(9, 9);
//   lcd::print("Vision");
//   lcd::setCursor(9, 32);
//   lcd::print("Ultrasonic");
//   }
//   if (SelectedAuton1 == 4) { // Purple Button
//   screen::draw_rect(0, 0, screenWidth/2, screenHeight/2, red);//red (1)
//   screen::draw_rect(0, screenHeight/2, screenWidth/2, screenHeight/2, yellow);//yellow (3)
//   screen::draw_rect(screenWidth/2, 0, screenWidth/2, screenHeight/2, blue);//blue (2)
//   screen::draw_rect(screenWidth/2, screenHeight/2, screenWidth/2, screenHeight/2, CSMGreen);///green (4)
//   lcd::setCursor(3, 9);
//   lcd::print("Skills 1");
//   lcd::setCursor(3, 33);
//   lcd::print("Skills 2");
//   lcd::setCursor(9, 9);
//   lcd::print("Skills 3");
//   lcd::setCursor(9, 33);
//   lcd::print("Skills 4");
//   }
//   ////////////////////////////////////////////////////////////////////////////////////////////////////
    
//   //This command blocks everything, but causes no issues because it is in the pre-auton, before the competition starts.
//   while(!lcd::pressing()  &&  !Controller1.ButtonX.pressing()){}//Waits until screen is pressed.

//   lcd::Clear();
//   int XCoor = lcd::xPosition();
//   int YCoor = lcd::yPosition();

//   int SelectedAuton2 = 0;

//   if (SelectedAuton1 == 1){
//     if ((XCoor >= 0 && XCoor <= screenWidth/2) && (YCoor >= 0 && YCoor <= screenHeight/2)) SelectedAuton2 = 1; //red red auton
//     else if ((XCoor >= 0 && XCoor <= screenWidth/2) && (YCoor >= screenHeight/2 && YCoor <= screenHeight)) SelectedAuton2 = 3; //red yellow auton

//     else if ((XCoor >= screenWidth/2 && XCoor <= screenWidth) && (YCoor >= 0 && YCoor <= screenHeight/2)) SelectedAuton2 = 2; // red blue auton
//     else if ((XCoor >= screenWidth/2 && XCoor <= screenWidth) && (YCoor >= screenHeight/2 && YCoor <= screenHeight)) SelectedAuton2 = 4; //red green auton
//   }

//   if (SelectedAuton1 == 2){
//     if ((XCoor >= 0 && XCoor <= screenWidth/2) && (YCoor >= 0 && YCoor <= screenHeight/2)) SelectedAuton2 = 5; //blue red auton
//     else if ((XCoor >= 0 && XCoor <= screenWidth/2) && (YCoor >= screenHeight/2 && YCoor <= screenHeight)) SelectedAuton2 = 7; //blue yellow auton

//     else if ((XCoor >= screenWidth/2 && XCoor <= screenWidth) && (YCoor >= 0 && YCoor <= screenHeight/2)) SelectedAuton2 = 6; // blue blue auton
//     else if ((XCoor >= screenWidth/2 && XCoor <= screenWidth) && (YCoor >= screenHeight/2 && YCoor <= screenHeight)) SelectedAuton2 = 8; //blue green auton
//   }

//   if (SelectedAuton1 == 3){
//     if ((XCoor >= 0 && XCoor <= screenWidth/2) && (YCoor >= 0 && YCoor <= screenHeight/2)) SelectedAuton2 = 9; //orange red auton
//     else if ((XCoor >= 0 && XCoor <= screenWidth/2) && (YCoor >= screenHeight/2 && YCoor <= screenHeight)) SelectedAuton2 = 11; //orange yellow auton

//     else if ((XCoor >= screenWidth/2 && XCoor <= screenWidth) && (YCoor >= 0 && YCoor <= screenHeight/2)) SelectedAuton2 = 10; // orange blue auton
//     else if ((XCoor >= screenWidth/2 && XCoor <= screenWidth) && (YCoor >= screenHeight/2 && YCoor <= screenHeight)) SelectedAuton2 = 12; //orange green auton
//   }

//   if (SelectedAuton1 == 4){
//     if ((XCoor >= 0 && XCoor <= screenWidth/2) && (YCoor >= 0 && YCoor <= screenHeight/2)) SelectedAuton2 = 13; //purple red auton
//     else if ((XCoor >= 0 && XCoor <= screenWidth/2) && (YCoor >= screenHeight/2 && YCoor <= screenHeight)) SelectedAuton2 = 15; //purple yellow auton

//     else if ((XCoor >= screenWidth/2 && XCoor <= screenWidth) && (YCoor >= 0 && YCoor <= screenHeight/2)) SelectedAuton2 = 14; // purple blue auton
//     else if ((XCoor >= screenWidth/2 && XCoor <= screenWidth) && (YCoor >= screenHeight/2 && YCoor <= screenHeight)) SelectedAuton2 = 16; //purple green auton
//   }


//   lcd::Clear();
//   delay(20);

//   switch (SelectedAuton2){
//     case 1:
//       screen::draw_rect(0, 0, screenWidth, screenHeight, red); // red red
//     break;

//     case 2:
//      screen::draw_rect(0, 0, screenWidth, screenHeight, blue); // red blue
//     break;

//     case 3:
//       screen::draw_rect(0, 0, screenWidth, screenHeight, yellow); // red yellow
//     break;

//     case 4:
//       screen::draw_rect(0, 0, screenWidth, screenHeight, CSMGreen); // red green
//     break;

//     case 5:
//       screen::draw_rect(0, 0, screenWidth, screenHeight, red); // blue red
//     break;

//     case 6:
//      screen::draw_rect(0, 0, screenWidth, screenHeight, blue); // blue blue
//     break;

//     case 7:
//       screen::draw_rect(0, 0, screenWidth, screenHeight, yellow); // blue yellow
//     break;

//     case 8:
//       screen::draw_rect(0, 0, screenWidth, screenHeight, CSMGreen); // blue green
//     break;

//     case 9:
//       screen::draw_rect(0, 0, screenWidth, screenHeight, red); // orange red
//     break;

//     case 10:
//      screen::draw_rect(0, 0, screenWidth, screenHeight, blue); // orange blue
//     break;

//     case 11:
//       screen::draw_rect(0, 0, screenWidth, screenHeight, yellow); // orange yellow
//     break;

//     case 12:
//       screen::draw_rect(0, 0, screenWidth, screenHeight, CSMGreen); // orange green
//     break;

//     case 13:
//       screen::draw_rect(0, 0, screenWidth, screenHeight, red); // purple red
//     break;

//     case 14:
//      screen::draw_rect(0, 0, screenWidth, screenHeight, blue); // purple blue
//     break;

//     case 15:
//       screen::draw_rect(0, 0, screenWidth, screenHeight, yellow); // purple yellow
//     break;

//     case 16:
//       screen::draw_rect(0, 0, screenWidth, screenHeight, CSMGreen); // purple green
//     break;

//     default:
//     break;

//   }

//   delay(500);
//   lcd::Clear();

//   return SelectedAuton2;

// }

// For trouble shooting, functions as a delay and makes the screen flash red
// void completionDelay(int delayTime) {
  
//   screen::draw_rect(0, 0, screenWidth, screenHeight, red);
//   delay((7*delayTime)/8);
//   lcd::clear();
//   delay(delayTime/8);

// }

// void start_timer(double sec) {

//   master_auton_seconds = sec;
//   Task countdown(master_auton_timer);

// }

// int master_auton_timer() {
//   if (master_auton_seconds > 0) {

//     double t = master_auton_seconds*1000;
//     double starttime = Brain.timer(msec);
//     double currrent_time;
//     bool iteration = true;

//     while(iteration) {

//       currrent_time = Brain.timer(msec);

//       if (((currrent_time-starttime) == t) || ((currrent_time-starttime) > t)) {

//         clear_master_auton_enable();
//         iteration = false;
//         break;

//       }

//     }

//   }

//   return 0;

// }