In an effort to not put a million comments in our code(making it hard to read and work on for the developers), but still give guidlines for other users we present the Odometry Documentation.

File Structure:
    The include and vex folders are for dependencies and configuration. Most of the relevant code is in src folder. main.cpp contains the Competition interface loop. robot-config.cpp contains the port configuration and the controller connection configuration as well as the program slot settings. functions.h contains functions that are used in main.cpp.

main.cpp:
    pre-auton:

    atounomous:

    user controll:

    main:

function.cpp:
    moveAll: take power arguemnt as a pct form and moves sets all six motors to that amount
    exitAuton: The procedure for exiting the PID loop invloving setting motion to zero and printing key details to the screen


