#include "vex.h"

//Constant variables for button positions.
//buttonX: location for pressable buttons
//buttonCompetitionY, buttonAutonY, buttonDriverY, buttonDebugY: placement of cursor on Y axis
//buttonWidth, buttonHeight: height and width of box being drawn
const int buttonX = 10;
const int buttonCompetitionY = 38;
const int buttonAutonY = 78;
const int buttonDriverY = 118;
const int buttonDebugY = 158;
const int buttonWidth = 150;
const int buttonHeight = 27;

void autonScreen(competition c);
void competitionScreen();
void buttonMechanics();
void __printXYZ(int x, int y, int z);
void __leftButtons();
void __bottomStatusBar();
void initializeScreen();

//Actual menu being printed, this prints after the initial
//Continue screen.
void menuScreen(){  
    Brain.Screen.setPenWidth(2);
    Brain.Screen.clearScreen("#000000");
    __leftButtons();
    __bottomStatusBar();
}

/***************************************************************************
* This function prints the competition screen and allows for choice of color, and 
* auton type.
*/
void autonScreen(competition c){
    if(c.isAutonomous()){
      Brain.Screen.clearScreen(red);
      Brain.Screen.setPenColor(white);
      Brain.Screen.setFont(propXXL);
      Brain.Screen.setCursor(3, 6);
      Brain.Screen.print("GULLS");
      for(int i = 60; i<200; i++){
        for(int j = 60; j<200; j++){
          if((j>=60&&j<=80)&&(i<=160)){
            Brain.Screen.setPenColor(red);
          }
          else{
            Brain.Screen.setPenColor(white);
          }
          Brain.Screen.drawPixel(j, i);
        }
      }
    }
}
void competitionScreen(){
  Brain.Screen.setFillColor("#808080");
  Brain.Screen.setPenColor(red);
  Brain.Screen.setCursor(2, 28);
  Brain.Screen.setFont(monoS);
  Brain.Screen.print("Welcome to the competition page!");
  Brain.Screen.setCursor(4, 28);
  Brain.Screen.print("Please choose a team and an auton.");
  Brain.Screen.setPenColor("#FFD700");
  Brain.Screen.setPenWidth(2);
  Brain.Screen.drawRectangle(230, 75, 220, 35, black);
  Brain.Screen.setPenColor(red);
  Brain.Screen.setPenWidth(4);
  Brain.Screen.setCursor(5, 20);
  Brain.Screen.setFont(propM);
  Brain.Screen.print("RED");
}
/*
  This function creates the mechanics for selection on the second page of the UI.
*/
void buttonMechanics(){
  //enum BUTTON{COMPETITION=0, DRIVERDEBUG = 1, AUTONDEBUG = 2, INFORMATION = 3};
  //int selector[4] = {COMPETITION, DRIVERDEBUG, AUTONDEBUG,INFORMATION};
  while(true){
    /*if((select.pressing()+UP.pressing()+DOWN.pressing()) ==3){
      initializeScreen();
    }*/
    
    //Competition menu
    if(Brain.Screen.pressing()==1){
      int x = Brain.Screen.xPosition();
      int y = Brain.Screen.yPosition();

      //Condition if competition button is pressed to call competition mode.
      if(((x>=buttonX && x<=buttonWidth) && (y>=buttonCompetitionY && y<= (buttonCompetitionY+buttonHeight)))||select.pressing()==1){
        competitionScreen();
      }
      //Condition if auton button is pressed to call competition mode.
      else if(((x>=buttonX && x<=buttonWidth) && (y>=buttonAutonY && y<= (buttonAutonY+buttonHeight)))||select.pressing()==1){
        Brain.Screen.setFillColor("#808080");
        Brain.Screen.setPenColor(red);
        Brain.Screen.setCursor(2, 35);
        Brain.Screen.setFont(monoXS);
        Brain.Screen.print("Welcome to driver debug");
      }
      //Condition if driver button is pressed to call competition mode.
      else if(((x>=buttonX && x<=buttonWidth)&&(y>=buttonDriverY && y<= (buttonDriverY+buttonHeight)))||select.pressing()==1){
        Brain.Screen.setFillColor("#808080");
        Brain.Screen.setPenColor(red);
        Brain.Screen.setCursor(2, 35);
        Brain.Screen.setFont(monoXS);
        Brain.Screen.print("Welcome to driver debug");
      }
      //Condition if debug button is pressed to call debug mode.
      else if(((x>=buttonX && x<=buttonWidth) && (y>=buttonDebugY && y<= (buttonDebugY+buttonHeight)))||select.pressing()==1){
        Brain.Screen.setFillColor("#808080");
        Brain.Screen.setPenColor(red);
        Brain.Screen.setCursor(2, 35);
        Brain.Screen.setFont(monoS);
        Brain.Screen.print("Welcome to the Auton debug");
        Brain.Screen.print("Please select a color");
      }
    }

    // driver debug
    /*else if(DOWN.pressing()==1||Brain.Screen.pressing()==1){
      int x = Brain.Screen.xPosition();
      int y = Brain.Screen.yPosition();
    }
    else if(DOWN.pressing()==1||Brain.Screen.pressing()==1){
      int x = Brain.Screen.xPosition();
      int y = Brain.Screen.yPosition();
    }
    else if(DOWN.pressing()==1||Brain.Screen.pressing()==1){
      int x = Brain.Screen.xPosition();
      int y = Brain.Screen.yPosition();
    }*/
  }
}

//This function allows the odom points to be passed through
void __printXYZ(int x, int y, int z){
    Brain.Screen.setPenWidth(12);
    Brain.Screen.setCursor(12, 30);
    Brain.Screen.print("(");
    Brain.Screen.print(x);
    Brain.Screen.print(", ");
    Brain.Screen.print(y);
    Brain.Screen.print(", ");
    Brain.Screen.print(z);
    Brain.Screen.print(")"); 
}

//Function to create the 4 buttons as well as the box for the menu
void __leftButtons(){
    //Sets color for the background of the buttons
    Brain.Screen.setPenColor("#808080");

    //Draws Box 1 for "Competition":
    Brain.Screen.drawRectangle(buttonX, buttonCompetitionY, buttonWidth, buttonHeight, "#808080");
    //Draws Box 2 for "Auton":
    Brain.Screen.drawRectangle(buttonX, buttonAutonY, buttonWidth, buttonHeight, "#808080");
    //Draws Box 3 for "Driver":
    Brain.Screen.drawRectangle(buttonX, buttonDriverY, buttonWidth, buttonHeight, "#808080");
    //Draws Box 4 for "Debug":
    Brain.Screen.drawRectangle(buttonX, buttonDebugY, buttonWidth, buttonHeight, "#808080");
    //Draws the box to the right of our buttons:
    Brain.Screen.drawRectangle(180, 38, 285, 147, "#808080");
    Brain.Screen.setFillColor("#808080");

    //Pen color for the letters
    Brain.Screen.setPenColor(black);
    //Button 1: 
    Brain.Screen.setCursor(3, 2);
    Brain.Screen.print("Competition");
    //Button 2:
    Brain.Screen.setCursor(5, 2);
    Brain.Screen.print("Auton");
    //Button 3:
    Brain.Screen.setCursor(7, 2);
    Brain.Screen.print("Driver");
    //Button 4:
    Brain.Screen.setCursor(9, 2);
    Brain.Screen.print("Debug");
}

//Function to create the bottom status bar:
  //Bottom status bar includes battery percentage, coordinates, team name
  //Controller status, and radio status.

  //Still missing controller status and radio status
void __bottomStatusBar(){
    //Sets pen color for the box
    Brain.Screen.setPenColor(red);
    //Draws and fills the rectangle at the bottom
    Brain.Screen.drawRectangle(0, 218, 480, 30, red);
    Brain.Screen.setFillColor(red);
    //Font color for the text
    Brain.Screen.setPenColor(white);
    Brain.Screen.setFont(propM);
    //Position to print team name / robot name
    Brain.Screen.setCursor(12, 13);
    Brain.Screen.print("GULLS");

    //Why is it setting the font twice, is this necessary?
    Brain.Screen.setFont(propM);

    //Prints coordinates from Odometry
    __printXYZ(1, 2, 3);

    //Position to place battery percentage
    Brain.Screen.setCursor(12, 42);
    Brain.Screen.print(Brain.Battery.capacity());
    Brain.Screen.print("%%");
}

/*
  This function prints the landing page for the UI.
  when called it will simply print the first screen
  This is beneficial for reseting the UI if a user so desires
*/

void initializeScreen(){
  Brain.Screen.clearScreen("000000");
  Brain.Screen.drawImageFromFile("Sammy.png", 9, 6);
  Brain.Screen.setPenWidth(4);
  Brain.Screen.setPenColor("#808080");
  Brain.Screen.drawRectangle(155, 145, 150, 40, "000000");
  Brain.Screen.setCursor(6, 12);
  Brain.Screen.setFont(monoL);
  Brain.Screen.setPenColor(white);
  Brain.Screen.setPenWidth(1);
  Brain.Screen.print("Continue");
  Brain.Screen.setPenColor(red);
  Brain.Screen.drawRectangle(0, 205, 480, 45, red);
  Brain.Screen.setFillColor(red);
  Brain.Screen.setPenColor(white);
  Brain.Screen.setFont(propL);
  Brain.Screen.setCursor(12, 13);
  Brain.Screen.print("GULLS");
  Brain.Screen.setFont(propM);
  __printXYZ(1, 2, 3);
  Brain.Screen.setCursor(12, 42);
  Brain.Screen.print(Brain.Battery.capacity());
  // % is an escape character so you must put 2 in order to print 
  Brain.Screen.print("%%");
  while(true){
    if(select.pressing() == 1||Brain.Screen.pressing() == 1){
      int x = Brain.Screen.xPosition();
      int y = Brain.Screen.yPosition();
      if(((x >= 160 && x <=360)&&(y >=170 && y <=220))||select.pressing()==1){
        menuScreen();
        buttonMechanics();
      }
    }
  }
}