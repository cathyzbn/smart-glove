/* 
File: flex.c
CS 107E Final Project
Cathy Zhou, Zhiyin Lin
----
This file contains functions to support reading from and interpreting the flex sensor.
 */
#include "mcp3008.h"
#include "printf.h"
#include "flex.h"

// constants for expected range of channels - five fingers
static int MAX_CHANNEL = 4;
static int MIN_CHANNEL = 0;

/* 
Function: valid_flex_channel
-----
Checks if the @param flex_channel is within expected range.
 */
int valid_flex_channel(unsigned int flex_channel){
    return flex_channel <= MAX_CHANNEL && flex_channel >= MIN_CHANNEL;
}

/* 
Function: read_flex
------
Reads from flex sensor with flex_channel
@return the value from ADC on the flex_channel reading
 */
int read_flex(unsigned int flex_channel){
    if (!valid_flex_channel(flex_channel)){
        return -1;
    }
    return mcp3008_read(flex_channel);
}

/* 
Function: is_flexed
------
Checks if a finger is bent all the way by angle
 */
int is_flexed(int angle){
    return (angle >= 70) && (angle <= 90);
}

/* 
Function: is_straight
------
Checks if a finger is straightened all the way by angle
 */
int is_straight(int angle){
    return (angle >= 0) && (angle <= 20); 
}

/* 
Function: is_bent
------
Checks if a finger is bent by angle
 */
int is_bent(int angle){
    return (angle >= 30) && (angle <= 70);
}

/* 
Function: is_slight_bent
------
Checks if a finger is bent slightly by angle
 */
int is_slight_bent(int angle){
    return (angle>=15) && (angle <= 40);
}

