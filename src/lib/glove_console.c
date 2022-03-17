/* 
File: glove_console.c
CS 107E Final Project
Cathy Zhou, Zhiyin Lin
----
Typing console using ASL. After initialization, the user will be able to "type" characters to the screen
using ASL and two additional characters (backspace and space). 
 */
#include "printf.h"
#include "uart.h"
#include "timer.h"

#include "flex.h"
#include "mcp3008.h"
#include "i2c_up.h"
#include "LSM6DS33.h"

#include "glove.h"
#include "console_up.h"

// console size constants
static unsigned int nrows = 20;
static unsigned int ncols = 50;

/* 
Function: glove_console
------
Initializes the glove, allows users to use ASL to "type" to the console
 */
void glove_console(void){
    // initialize sensors
    i2c_init();
    lsm6ds33_init();
    mcp3008_init();

    // initialize glove
    struct Glove glove;
    printf("Begin initialization. \n");
    glove_init_min(&glove);
    glove_init_max(&glove);
    printf("End initialization. \n");

    // initialize console
    console_init(nrows, ncols, GL_WHITE, GL_INDIGO);

    while (true){

        char c = glove_read_char(&glove, 1); 
        if (c == '*'){
            continue;
        }
        if (c == '\b'){
            console_printf("%c", '\b');
            console_printf("%c", ' ');
        }
        console_printf("%c", c);
    }
}