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

//prototype functions
void autonScreen(competition, color);
void competitionScreen();
void __buttonMechanics();
void __printXYZ(int, int, int);
void __leftButtons();
void __drawBottomStatusBar();
void landingPage();
void __updateBottomStatusBar();
void debugDriver();
void debugAuton();
void infoPage();

//Actual menu being printed, this prints after the initial
//Continue screen.
void menuScreen(){
    Brain.Screen.setPenWidth(2);
    Brain.Screen.clearScreen("#000000");
    __leftButtons();
    __drawBottomStatusBar();
    __buttonMechanics();
}

/***************************************************************************
* This function prints the competition screen and allows for choice of color, and 
* auton type.
*/
void autonScreen(competition c, color team){
    if(c.isAutonomous()){
      Brain.Screen.clearScreen(team);
      Brain.Screen.setPenColor(white);
      Brain.Screen.setFont(propXXL);
      Brain.Screen.setCursor(3, 6);
      Brain.Screen.print("GULLS");
    }
    else if(c.isDriverControl()){
      Brain.Screen.clearScreen(team);
    }
}
/*
* This function prints the competition screen to select a color and an autonomous type
* -Function then places the robot in the correct state for each condition
*/
void competitionScreen(){
  Brain.Screen.clearScreen("#808080");
  Brain.Screen.setPenColor(red);
  Brain.Screen.setCursor(5, 5);
  Brain.Screen.setFont(monoS);
  Brain.Screen.print("Welcome to the competition page!");
  Brain.Screen.setCursor(8, 5);
  Brain.Screen.print("Please choose a team and an auton.");
  Brain.Screen.setPenColor("#FFD700");
  Brain.Screen.setPenWidth(2);
  Brain.Screen.drawRectangle(25, 8, 5, 10);
  Brain.Screen.drawCircle(25, 8, 2);
  Brain.Screen.drawCircle(25, 10, 2);
  Brain.Screen.drawCircle(30, 8, 2);
  Brain.Screen.drawCircle(30, 10, 2);
  Brain.Screen.setPenColor(red);
  Brain.Screen.setPenWidth(4);
  Brain.Screen.setCursor(5, 20);
  Brain.Screen.setFont(propM);
  Brain.Screen.print("RED");
}
//function to print the debug autonomous screen
void debugAuton(){
  //select an autonomous and choose color

}
//function to print the driver screen
void debugDriver(){
  // select a color and allow driver to 

}
//function to print the information page
void infoPage(){

}
/*
  This function creates the mechanics for selection on the second page of the UI.
*/
void __buttonMechanics(){
  enum BUTTON{COMPETITION=0, DRIVERDEBUG = 1, AUTONDEBUG = 2, INFORMATION = 3};
  int selector[4] = {COMPETITION, DRIVERDEBUG, AUTONDEBUG,INFORMATION};
  int locator =0;
  bool selected = false;
  while(!selected){
    //if a button is selected, the rest of the button mechanics are called
    if(select.pressing()==1 || UP.pressing()==1 || DOWN.pressing()==1 || Brain.Screen.pressing()==1){
      selected = true;
    }
  }

  while(selected){
    menuScreen();
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
        competitionScreen();
      }
      //Condition if driver button is pressed to call competition mode.
      else if(((x>=buttonX && x<=buttonWidth)&&(y>=buttonDriverY && y<= (buttonDriverY+buttonHeight)))||select.pressing()==1){
        
      }
      //Condition if debug button is pressed to call debug mode.
      else if(((x>=buttonX && x<=buttonWidth) && (y>=buttonDebugY && y<= (buttonDebugY+buttonHeight)))||select.pressing()==1){
        
      }
    }
    // condition if select is pressed
    // checking each condition of the selector
    else if(select.pressing()==1){
      //condition if the selector is at the first button
      if(selector[locator]==0){
        competitionScreen();
      }
      //condition if the selector is at the second button
      else if(selector[locator]==1){
        debugAuton();
      }
      //condition if the selector is at the third button
      else if(selector[locator]==2){
        debugDriver();
      }
      //condition if the selector is at the fourth button
      else if(selector[locator]==3){
        infoPage();
      }
    }
    // condition to move button down 1 or set to 0 if it reaches 3
    else if(DOWN.pressing()==1){
      //reset condition
      if(locator==3){
        locator=0;
      }
      //condition for moving the locator down
      else
        locator++;
    }
    // condition to move button up 1 or set to 3 if it reaches 0
    else if(UP.pressing()==1){
      //reset condition
      if(locator==0){
        locator=3;
      }
      //condition to move button up
      else
        locator--;
    }
    wait(5, msec);
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
void __drawBottomStatusBar(){
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
    __updateBottomStatusBar();

}

void __updateBottomStatusBar(){
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

void landingPage(){
  // clearScreen and set color to black
  Brain.Screen.clearScreen("#000000");
  // draw image from file
  Brain.Screen.setPenWidth(4);
  Brain.Screen.setPenColor("#808080");
  Brain.Screen.drawRectangle(155, 145, 150, 40, "000000");
  Brain.Screen.setCursor(6, 12);
  Brain.Screen.setFont(monoL);
  Brain.Screen.setPenColor(white);
  Brain.Screen.setPenWidth(1);
  Brain.Screen.print("Continue");
  Brain.Screen.drawImageFromFile("download.png", 160, 40);
  __drawBottomStatusBar();
  __buttonMechanics();

  }