/* 
File: teacher.c
CS 107E Final Project
Cathy Zhou, Zhiyin Lin
----
Teacher module for ASL learning. 
After calibration, this module will give user instructions to gesture certain characters.
The module will give feedback to users on whether their gesture is correct or not.
 */

#include "console_up.h"
#include "timer.h"
#include "mcp3008.h"
#include "printf.h"
#include "flex.h"
#include "glove.h"
#include "LSM6DS33.h"
#include "i2c_up.h"
#include "strings.h"

// console constants
static unsigned int nrows = 20;
static unsigned int ncols = 50;

/* 
Function: teacher
-------
This function starts the teacher module. It initializes the glove, gives users instructions for gesturing, 
and gives feedback to users on whether their gesture is correct or not.
 */
void teacher(void){
    // initialize console
    console_init(nrows, ncols, GL_WHITE, GL_INDIGO);
    console_printf("Hi! Welcome to the world of ASL :) This magical glove will be your TA this quarter!\n\n");
    timer_delay(2);
    console_printf("We hope to provide feedback on your ASL and help you learn the gestures!\n");
    timer_delay(2);

    // initialize sensors
    i2c_init();
    lsm6ds33_init();
    mcp3008_init();


    // initialize glvoe
    struct Glove glove;
    console_printf("Begin calibrating min. Curl your fingers. You have five seconds.");
    glove_init_min(&glove);
    console_printf("Begin calibrating max. Put your fingers straight. You have five seconds.");
    glove_init_max(&glove);
    console_printf("Your glove is initialized. Let's start learning! \n");

    // randomized characters
    char tests[] = {'A', 'L', 'X', 'N', 'T', 'P', 'W', 'C', 'M', 'I', 'Y', 'S', 'B', 'O', 'Q', 'Z', 'D', 'G', 'U', 'H', 'J', 'F', 'K', 'E', 'V', 'R'};
    
    // loop through all characters, circle back if reach the end
    int i=0;
    while(1){
        console_printf("Gesture the ASL for the character %c\n", tests[i]);
        int passed = 0;
        // loops until the user gestures correclty
        while(passed == 0){
            char c = glove_read_char(&glove, 5);
            // if the user is correct
            if (c == tests[i]){
                passed = 1;
                console_printf("Congrats! you got it!\n\n");
            } 
            // if the user is incorrect
            else {
                console_printf("Your gesture for %c is a little off track. We read %c. Try again!\n", tests[i], c);
            }
        }
        // increment
        i = (i+1)%26;
    }
}