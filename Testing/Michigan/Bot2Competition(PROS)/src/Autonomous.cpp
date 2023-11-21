#include "Autonomous.h"

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

void Autonomous() {
  isAuton = true; resetPID = true; resetTurning = true; resetFlywheel = true; isUser = false;
    Task StartAuton(autonController);

    /*
    //example of how to use functions

    //moves the bot the provided amount of inches (roughly)
    //i wouldnt use a tape measurer to get the distance for these but rather tune each one
    //until it moves the way you want
    MoveBot(12);

    //rotates the bot clockwise? the amout of degrees provided (even more roughly)
    //this function needs to be tuned to how you want even more than movebot
    RotateBot(90);

    //send true to turn the intake motor on, false to turn it off
    //can also use second parameter to tell a specific power, default 100
    IntakeBalls(true, 40);

    //spins the intake backwards to outake any balls
    //not sure if will be used in auton but will be used in user
    //second paramter tells power to send motor if desired, default 100
    OuttakeBalls(true, 70);

    //shoots the current ball and gets the program ready to reload the catapult
    //if given a parameter, the program will wait that long in milliseconds after shooting to continue. default 0
    ShootBall(100);
    */
   
    // MoveBot(16);
    master.print(0, 0, "PID Called");
    // RotateBot(90);
    // MoveBot(16);
    // RotateBot(-90);
    // MoveBot(-16);
    
    MoveBot(6);
    RotateBot(45);
    MoveBot(6);
    RotateBot(-90);
    MoveBot(6);
    MoveBot(-5);
    RotateBot(90);
    MoveBot(6);
    RotateBot(45);
    MoveBot(6);
    MoveBot(-5);
    RotateBot(135);
    MoveBot(6);
    RotateBot(-45);
    MoveBot(6);
}