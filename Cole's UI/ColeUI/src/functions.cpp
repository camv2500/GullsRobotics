#include "vex.h"
#include "robot-config.h"

//Constant variables for button positions.
//buttonX: location for pressable buttons
//buttonCompetitionY, buttonAutonY, buttonDriverY, buttonDebugY: placement of cursor on Y axis
//buttonWidth, buttonHeight: height and width of box being drawn
const int mainButtonX = 155;
const int mainButtonY = 145;
const int mainWidth = 150;
const int mainHeight = 40;
const int buttonX = 10;
const int buttonCompetitionY = 38;
const int buttonAutonY = 78;
const int buttonDriverY = 118;
const int buttonDebugY = 158;
const int buttonWidth = 150;
const int buttonHeight = 27;
 
//constant values for the odometry 
const int value1 = 6;
const int value2 = 0;
const int value3 = 0;

//prototype functions
void landingPage();
void menuScreen();
void autonScreen(competition, color);
void competitionScreen();
void driverPage();
void autonPage();
void debugPage();
void __buttonMechanics();
void __printXYZ(int, int, int);
void __leftButtons1(int);
void __leftButtons2(int);
void __leftButtons3(int);
void __leftButtons4(int);
void __drawBottomStatusBar();
void __updateBottomStatusBar();
void __infoBlock();
void __continueButton(int);

/*
  This function prints the landing page for the UI.
  when called it will simply print the first screen
  This is beneficial for reseting the UI if a user so desires
*/
void landingPage(){
  // clearScreen and set color to black
  Brain.Screen.clearScreen("#000000");
  // set pen width to 4 pixels
  __continueButton(0);
  // print sammy the seagull to the landing page
  Brain.Screen.drawImageFromFile("sammyTheSeagull.png", 175, 10);
  Brain.Screen.drawImageFromFile("VEXU.png", 10, 50);
  Brain.Screen.drawImageFromFile("VEXU.png", 370, 50);
  // call function to print the bottom status bar
  __drawBottomStatusBar();
  // call the logic that makes the screen pressing and buttons work
  __buttonMechanics();

}
//Actual menu being printed, this prints after the initial
//Continue screen.
void menuScreen(){
    Brain.Screen.setPenWidth(2);
    Brain.Screen.clearScreen("#000000");
    //initialize the left buttons
    __leftButtons1(0);
    __leftButtons2(0);
    __leftButtons3(0);
    __leftButtons4(0);
    //initialize the info block that sits to the left of the buttons
    __infoBlock();
    // draw the status bar
    __drawBottomStatusBar();
}

/***************************************************************************
* This function takes in a competition variable and color and initializes a license plate 
*/
void autonScreen(competition c, color team){
    //case for when in auton 
    if(c.isAutonomous()){
      Brain.Screen.clearScreen(team);
      Brain.Screen.setPenColor(white);
      Brain.Screen.setFont(propXXL);
      Brain.Screen.setCursor(3, 6);
      Brain.Screen.print("GULLS");
    }
    //case for when in auton
    else if(c.isDriverControl()){
      Brain.Screen.clearScreen(team);
    }
}
/*
* This function prints the competition screen to select a color and an autonomous type
* -Function then places the robot in the correct state for each condition
  for sake of cleanliness i left this block without comments 
*/
void competitionScreen(){
  Brain.Screen.clearScreen("#808080");
  Brain.Screen.setPenColor(black);
  Brain.Screen.setFillColor("#808080");
  Brain.Screen.setCursor(1, 1);
  Brain.Screen.setFont(monoM);
  Brain.Screen.print("Welcome to the competition page!");
  Brain.Screen.setCursor(3, 4);
  Brain.Screen.print("Please choose a team and an auton below:");
  Brain.Screen.setPenColor(red);
  Brain.Screen.setPenWidth(4);
  Brain.Screen.setCursor(7, 3);
  Brain.Screen.setFont(propM);
  Brain.Screen.print("RED TEAM");
  Brain.Screen.drawRectangle(120, 100, 320, 48, black);
  Brain.Screen.setPenColor(blue);
  Brain.Screen.drawRectangle(120, 175, 320, 48, black);
  Brain.Screen.setCursor(10, 2);
  Brain.Screen.print("BLUE TEAM");
}
//function to print the debug autonomous screen
void autonPage(){
  //select an autonomous and choose color
  Brain.Screen.clearScreen("#808080");
  Brain.Screen.setCursor(1, 1);
  Brain.Screen.print("Auton");
}
//function to print the driver screen
void driverPage(){
  // select a color and allow driver to 
  Brain.Screen.clearScreen("#808080");
  Brain.Screen.setCursor(1, 1);
  Brain.Screen.print("Driver");
}
//function to print the debug screen
void debugPage(){
  Brain.Screen.clearScreen("#808080");
  Brain.Screen.setCursor(1, 1);
  Brain.Screen.print("debug");
}
/*
  This function creates the mechanics for selection on the second page of the UI.
*/
void __buttonMechanics(){
  // create an enumerated list to visualize button mechanics better
  enum BUTTON{COMPETITION=0, AUTONPAGE = 1, DRIVERPAGE = 2, DEBUGPAGE = 3};
  // locator tracks the button value
  int locator =0;
  // selected is a boolean value which is changed when the mechanics is in the landing page 
  bool selected = false;
  // this while loop runs while in the landing screen 
  while(!selected){
    //if a button is selected, the rest of the button mechanics are called
    if(select.pressing()==1){
      selected = true;
      menuScreen();
      wait(1, sec);
    }
    else if(Brain.Screen.pressing()==1){
      int x = Brain.Screen.xPosition();
      int y = Brain.Screen.yPosition();
      if((x>=mainButtonX && x<=mainButtonX+mainWidth)&&(y>=mainButtonY&&y<=mainButtonY+mainHeight)){
        selected = true;
        // print the continue button except lightly shaded to show it being pressed
        __continueButton(1);
        // wait for 1 second to avoid pressing into the wrong screen
        wait(1, sec);
        // print the main screen
        menuScreen();
      }
    }
  }
  // while loop for the main screen
  while(selected){
    //Competition menu
    if(Brain.Screen.pressing()==1){
      int x = Brain.Screen.xPosition();
      int y = Brain.Screen.yPosition();

      //Condition if competition button is pressed to call competition mode.
      if(((x>=buttonX && x<=(buttonX+buttonWidth)) && (y>=buttonCompetitionY && y<= (buttonCompetitionY+buttonHeight)))){
        __leftButtons1(1);
        wait(1, sec);
        competitionScreen();
      }
      //Condition if auton button is pressed to call competition mode.
      else if(((x>=buttonX && x<=buttonWidth) && (y>=buttonAutonY && y<= (buttonAutonY+buttonHeight)))){
        __leftButtons2(1);
        wait(1, sec);
        autonPage();
      }
      //Condition if driver button is pressed to call competition mode.
      else if(((x>=buttonX && x<=buttonWidth)&&(y>=buttonDriverY && y<= (buttonDriverY+buttonHeight)))){
        __leftButtons3(1);
        wait(1, sec);
        driverPage();
      }
      //Condition if debug button is pressed to call debug mode.
      else if(((x>=buttonX && x<=buttonWidth) && (y>=buttonDebugY && y<= (buttonDebugY+buttonHeight)))){
        __leftButtons4(1);
        wait(1, sec);
        debugPage();
      }
    }
    // condition if select is pressed
    // checking each condition of the selector
    else if(select.pressing()==1){
      //condition if the selector is at the first button
      if(locator==COMPETITION){
        competitionScreen();
        __leftButtons1(1);
      }
      //condition if the selector is at the second button
      else if(locator==AUTONPAGE){
        autonPage();
        __leftButtons2(1);
      }
      //condition if the selector is at the third button
      else if(locator==DRIVERPAGE){
        driverPage();
        __leftButtons3(1);
      }
      //condition if the selector is at the fourth button
      else if(locator==DEBUGPAGE){
        debugPage();
        __leftButtons4(1);
      }
    }
    // condition to move button down 1 or set to 0 if it reaches 3
    else if(DOWN.pressing()==1){
      //reset condition
      if(locator==DEBUGPAGE){
        locator=COMPETITION;
      }
      //condition for moving the locator down
      else
        locator++;
    }
    // condition to move button up 1 or set to 3 if it reaches 0
    else if(UP.pressing()==1){
      //reset condition
      if(locator==COMPETITION){
        locator=DEBUGPAGE;
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
    Brain.Screen.setCursor(12, 31);
    Brain.Screen.print("(");
    Brain.Screen.print(x);
    Brain.Screen.print(", ");
    Brain.Screen.print(y);
    Brain.Screen.print(", ");
    Brain.Screen.print(z);
    Brain.Screen.print(")"); 
}
// Function to create the side block holding information regarding the UI/team/changeable information
void __infoBlock(){
    Brain.Screen.drawRectangle(180, 38, 285, 147, "#808080");
    Brain.Screen.setPenColor(black);
    Brain.Screen.setCursor(5, 34);
    Brain.Screen.setFont(monoXS);
    Brain.Screen.print("Hello!");
    Brain.Screen.setCursor(6, 34);
    Brain.Screen.print("Welcome to Salisbury University's UI");
    Brain.Screen.setCursor(7, 34);
    Brain.Screen.print("");
}
//Function to create the 4 buttons as well as the box for the menu
void __leftButtons1(int value){
    if(value == 0){
        Brain.Screen.setFont(monoM);
        Brain.Screen.setFillColor("#808080");
        //Sets color for the background of the buttons
        Brain.Screen.setPenColor("#808080");
        //Draws Box 1 for "Competition":
        Brain.Screen.drawRectangle(buttonX, buttonCompetitionY, buttonWidth, buttonHeight, "#808080");

        //Pen color for the letters
        Brain.Screen.setPenColor(black);
        //Button 1: 
        Brain.Screen.setCursor(3, 2);
        Brain.Screen.print("Competition");
    }
    else{
        Brain.Screen.setFont(monoM);
        Brain.Screen.setFillColor("#d3d3d3 ");
        //Sets color for the background of the buttons
        Brain.Screen.setPenColor("#d3d3d3 ");
        //Draws Box 1 for "Competition":
        Brain.Screen.drawRectangle(buttonX, buttonCompetitionY, buttonWidth, buttonHeight, "#d3d3d3");

        //Pen color for the letters
        Brain.Screen.setPenColor(black);
        //Button 1: 
        Brain.Screen.setCursor(3, 2);
        Brain.Screen.print("Competition");
    }
}
void __leftButtons2(int value){
    if(value == 0){
        Brain.Screen.setFont(monoM);
        Brain.Screen.setFillColor("#808080");
        //Sets color for the background of the buttons
        Brain.Screen.setPenColor("#808080");
        //Draws Box 2 for "Auton":
        Brain.Screen.drawRectangle(buttonX, buttonAutonY, buttonWidth, buttonHeight, "#808080");
        //Pen color for the letters
        Brain.Screen.setPenColor(black);
        //Button 2:
        Brain.Screen.setCursor(5, 2);
        Brain.Screen.print("Auton");
    }
    else{
        Brain.Screen.setFont(monoM);
        Brain.Screen.setFillColor("#d3d3d3");
        //Sets color for the background of the buttons
        Brain.Screen.setPenColor("#d3d3d3");
        //Draws Box 2 for "Auton":
        Brain.Screen.drawRectangle(buttonX, buttonAutonY, buttonWidth, buttonHeight, "#d3d3d3");
        //Pen color for the letters
        Brain.Screen.setPenColor(black);
        //Button 2:
        Brain.Screen.setCursor(5, 2);
        Brain.Screen.print("Auton");
    }
}
void __leftButtons3(int value){
    if(value == 0){
        Brain.Screen.setFont(monoM);
        Brain.Screen.setFillColor("#808080");
        //Sets color for the background of the buttons
        Brain.Screen.setPenColor("#808080");
        //Draws Box 3 for "Driver":
        Brain.Screen.drawRectangle(buttonX, buttonDriverY, buttonWidth, buttonHeight, "#808080");
        //Pen color for the letters
        Brain.Screen.setPenColor(black);
        //Button 3:
        Brain.Screen.setCursor(7, 2);
        Brain.Screen.print("Driver");
    }
    else{
        Brain.Screen.setFont(monoM);
        Brain.Screen.setFillColor("#d3d3d3");
        //Sets color for the background of the buttons
        Brain.Screen.setPenColor("#d3d3d3");
        //Draws Box 3 for "Driver":
        Brain.Screen.drawRectangle(buttonX, buttonDriverY, buttonWidth, buttonHeight, "#d3d3d3");
        //Pen color for the letters
        Brain.Screen.setPenColor(black);
        //Button 3:
        Brain.Screen.setCursor(7, 2);
        Brain.Screen.print("Driver");
    }
}
void __leftButtons4(int value){
    if(value == 0){
        Brain.Screen.setFont(monoM);
        Brain.Screen.setFillColor("#808080");
        //Sets color for the background of the buttons
        Brain.Screen.setPenColor("#808080");
        //Draws Box 4 for "Debug":
        Brain.Screen.drawRectangle(buttonX, buttonDebugY, buttonWidth, buttonHeight, "#808080");
        //Pen color for the letters
        Brain.Screen.setPenColor(black);
        //Button 4:
        Brain.Screen.setCursor(9, 2);
        Brain.Screen.print("Debug");
    }
    else{
        Brain.Screen.setFont(monoM);
        Brain.Screen.setFillColor("#d3d3d3");
        //Sets color for the background of the buttons
        Brain.Screen.setPenColor("#d3d3d3");
        //Draws Box 4 for "Debug":
        Brain.Screen.drawRectangle(buttonX, buttonDebugY, buttonWidth, buttonHeight, "#d3d3d3");
        //Pen color for the letters
        Brain.Screen.setPenColor(black);
        //Button 4:
        Brain.Screen.setCursor(9, 2);
        Brain.Screen.print("Debug");
    }
}
/* this function prints the continue button in 2 different states
  First state is the normal button print
  Second state is the pressed button print
  the checker would be a value of something being pressed
*/
void __continueButton(int checker){
  Brain.Screen.setFillColor("#000000");
  //case for the normal button to print
  if(checker == 0){
      Brain.Screen.setPenWidth(4);
      // set pen color to grey
      Brain.Screen.setPenColor("#808080");
      // Draw main screen continue button
      Brain.Screen.drawRectangle(mainButtonX, mainButtonY, mainWidth, mainHeight, "000000");
      // set the cursor
      Brain.Screen.setCursor(6, 12);
      // set to larger font
      Brain.Screen.setFont(monoL);
      // set pen color to white for drawing continue
      Brain.Screen.setPenColor(white);
      // set the pen width to 1 pixel
      Brain.Screen.setPenWidth(1);
      // print continue
      Brain.Screen.print("Continue");
  }
  //case for when the button needs to appear pressed
  else if(checker == 1){
      Brain.Screen.setFillColor("#424242");
      Brain.Screen.setPenWidth(4);
      // set pen color to grey
      Brain.Screen.setPenColor("#D0D3D4");
      // Draw main screen continue button
      Brain.Screen.drawRectangle(mainButtonX, mainButtonY, mainWidth, mainHeight, "#424242");
      // set the cursor
      Brain.Screen.setCursor(6, 12);
      // set to larger font
      Brain.Screen.setFont(monoL);
      // set pen color to white for drawing continue
      Brain.Screen.setPenColor(white);
      // set the pen width to 1 pixel
      Brain.Screen.setPenWidth(1);
      // print continue
      Brain.Screen.print("Continue");
  }
}

/*Function to create the bottom status bar:
  Bottom status bar includes battery percentage, coordinates, team name
  Controller status, and radio status.
  still missing controller status and radio status
  */
void __drawBottomStatusBar(){
    Brain.Screen.setPenWidth(2);
    //Sets pen color for the box
    Brain.Screen.setPenColor(red);
    //Draws and fills the rectangle at the bottom
    Brain.Screen.drawRectangle(0, 218, 480, 30, red);
    Brain.Screen.setFillColor(red);
    //Font color for the text
    Brain.Screen.setPenColor(white);
    Brain.Screen.setFont(propM);
    //Position to print team name / robot name
    Brain.Screen.setCursor(12, 21);
    Brain.Screen.print("GULLS");

    //Why is it setting the font twice, is this necessary?
    Brain.Screen.setFont(propM);
    __updateBottomStatusBar();

}

/*
  This function updates the values of the odometry values and the battery percentage
*/
void __updateBottomStatusBar(){
    //Prints coordinates from Odometry
    __printXYZ(value1, value2, value3);
    
    //Position to place battery percentage
    Brain.Screen.setCursor(12, 43);
    Brain.Screen.print(Brain.Battery.capacity());
    Brain.Screen.print("%%");

}