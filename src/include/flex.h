#ifndef FLEX_H
#define FLEX_H

/* 
Function: valid_flex_channel
-----
Checks if the @param flex_channel is within expected range.
 */
int valid_flex_channel(unsigned int flex_channel);

/* 
Function: read_flex
------
Reads from flex sensor with flex_channel
@return the value from ADC on the flex_channel reading
 */
int read_flex(unsigned int flex_channel);


/* 
Function: is_flexed
------
Checks if a finger is bent all the way by angle
 */
int is_flexed(int angle);

/* 
Function: is_straight
------
Checks if a finger is straightened all the way by angle
 */
int is_straight(int angle);

/* 
Function: is_bent
------
Checks if a finger is bent by angle
 */
int is_bent(int angle);

/* 
Function: is_slight_bent
------
Checks if a finger is bent slightly by angle
 */
int is_slight_bent(int angle);

#endif