#ifndef FLEX_H
#define FLEX_H
// #include "gpio.h"

int valid_flex_channel(unsigned int flex_channel);

int read_flex(unsigned int flex_channel);

enum {
    CH0 = 0,
    CH1 = 1,
    CH2 = 2,
    CH3 = 3,
    CH4 = 4,
};




#endif