#include "mcp3008.h"
#include "printf.h"
#include "flex.h"

/* 
Struct: Glove
----
Holds the flex's sensor's minimum and maximum values, 
their calculated angles, and the accelerometer's gap readings.
 */
struct Glove{
    int sensorMin1;
    int sensorMin2;
    int sensorMin3;
    int sensorMin4;
    int sensorMin5;

    int sensorMax1;
    int sensorMax2;
    int sensorMax3;
    int sensorMax4;
    int sensorMax5;

    float angle1;
    float angle2;
    float angle3;
    float angle4;
    float angle5;

    short gap;
};




/* 
Function: glove_init_min
------
Instructs users to calibrate minimum for the sensors (curl fingers).

Reads from flex sensor and finds the minimum value read for each sensor.
Stores the values read into the `glove` struct.
prints the calibration and parameters
 */
void glove_init_min();

/* 
Function: glove_init_max
------
Instructs users to calibrate maximum for the sensors (straight fingers).

Reads from flex sensor and finds the maximum value read for each sensor.
Stores the values read into the `glove` struct.
prints the calibration and parameters
 */
void glove_init_max();

/* 
Function: glove_read_char
------
@param glove: the struct for the glove
@param sec: number of seconds to read a character

contains the decision process to decide on the character for ASL.
 */
char glove_read_char();

/* 
Function: get_angle
-----
supports getting angle at the finger @param flex_channel in the number of seconds @param sec
reads from the glove @param glove
 */
int get_angle(int flex_channel, struct Glove* glove, int sec);
