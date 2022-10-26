#include "vex.h"
void initializeScreen();
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
    if((select.pressing()+UP.pressing()+DOWN.pressing()) ==3){
      initializeScreen();
    }
    }
    //Competition menu
    if(Brain.Screen.pressing()==1){
      int x = Brain.Screen.xPosition();
      int y = Brain.Screen.yPosition();
      if(((x>=5 && x<=155)&&(y>=15 && y<=47))||select.pressing()==1){
        competitionScreen();
      }
      else if(((x>=5&&x<=155)&&(y>=65&&y<=95))||select.pressing()==1){
        Brain.Screen.setFillColor("#808080");
        Brain.Screen.setPenColor(red);
        Brain.Screen.setCursor(2, 35);
        Brain.Screen.setFont(monoXS);
        Brain.Screen.print("Welcome to driver debug");
      }
      else if(((x>=5&&x<=155)&&(y>=65&&y<=95))||select.pressing()==1){
        Brain.Screen.setFillColor("#808080");
        Brain.Screen.setPenColor(red);
        Brain.Screen.setCursor(2, 35);
        Brain.Screen.setFont(monoXS);
        Brain.Screen.print("Welcome to driver debug");
      }
      else if(((x>=5&&x<=155)&&(y>=115&&y<=145))||select.pressing()==1){
        Brain.Screen.setFillColor("#808080");
        Brain.Screen.setPenColor(red);
        Brain.Screen.setCursor(2, 35);
        Brain.Screen.setFont(monoS);
        Brain.Screen.print("Welcome to the Auton debug");
        Brain.Screen.print("Please select a color");
      }
      else if((x>=5&&x<=155)&&(y>=165&&y<=195)){
        Brain.Screen.setFillColor("#808080");
        Brain.Screen.setPenColor(red);
        Brain.Screen.setCursor(2, 30);
        Brain.Screen.setFont(monoS);
        Brain.Screen.print("This is just robot info:");
        Brain.Screen.setCursor(2, 37);
        Brain.Screen.print("hello");
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
/*
  This function allows for the location units to be placed inside the parenthesis.
*/
void printXYZ(int x, int y, int z){
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
/*
  This function print the menu.
*/
void menuScreen(){
    Brain.Screen.setPenWidth(2);
    Brain.Screen.clearScreen("#000000");
    Brain.Screen.setPenColor("#808080");
    Brain.Screen.drawRectangle(5,15, 150, 30, "#808080");
    Brain.Screen.drawRectangle(5, 65, 150, 30, "#808080");
    Brain.Screen.drawRectangle(5, 115, 150, 30, "#808080");
    Brain.Screen.drawRectangle(5, 165, 150, 30, "#808080");
    Brain.Screen.drawRectangle(180, 5, 285, 185, "#808080");
    Brain.Screen.setFillColor("#808080");
    Brain.Screen.setPenColor(black);
    Brain.Screen.setCursor(2, 3);
    Brain.Screen.print("Competition");
    Brain.Screen.setPenColor(red);
    Brain.Screen.drawRectangle(0, 205, 480, 45, red);
    Brain.Screen.setFillColor(red);
    Brain.Screen.setPenColor(white);
    Brain.Screen.setFont(propL);
    Brain.Screen.setCursor(12, 13);
    Brain.Screen.print("GULLS");
    Brain.Screen.setFont(propM);
    printXYZ(1, 2, 3);
    Brain.Screen.setCursor(12, 42);
    Brain.Screen.print(Brain.Battery.capacity());
    Brain.Screen.print("%%");
}
/*
  This function prints the landing page for the UI.
  when called it will simply print the first screen
  /This is beneficial for reseting the UI if a user so desires
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
  printXYZ(1, 2, 3);
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