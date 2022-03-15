#include "console_up.h"
#include "timer.h"
#include "mcp3008.h"
#include "printf.h"
#include "flex.h"
#include "glove.h"
#include "LSM6DS33.h"
#include "i2c_up.h"
#include "strings.h"

static unsigned int nrows = 20;
static unsigned int ncols = 50;


void teacher(void){
    console_init(nrows, ncols, GL_WHITE, GL_INDIGO);
    console_printf("Hi! Welcome to the world of ASL :) This magical glove will be your TA this quarter!\n\n");
    timer_delay(2);
    console_printf("We hope to provide feedback on your ASL and help you learn the gestures!\n");
    timer_delay(2);

    i2c_init();
    lsm6ds33_init();
    mcp3008_init();

    console_printf("Your glove is initialized. Let's start learning! \n");

    struct Glove glove;
    glove_init_min(&glove);
    glove_init_max(&glove);

    console_printf("End init. \n");

    char tests[] = {'A', 'L', 'X', 'N', 'T', 'P', 'W', 'C', 'M', 'I', 'Y', 'S', 'B', 'O', 'Q', 'Z', 'D', 'G', 'U', 'H', 'J', 'F', 'K', 'E', 'V', 'R'};
    int i=0;
    while(1){
        console_printf("Gesture the ASL for the character %c\n", tests[i]);
        int passed = 0;
        while(passed == 0){
            char c = glove_read_char(&glove, 5);
            if (c == tests[i]){
                passed = 1;
                console_printf("Congrats! you got it!\n\n");
            } else {
                console_printf("Your gesture for %c is a little off track. We read %c. Try again!\n", tests[i], c);
            }
        }
        console_printf("null");
        i = (i+1)%26;
    }
}