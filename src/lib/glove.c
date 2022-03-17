 
/* 
File: glove.c
CS 107E Final Project
Cathy Zhou, Zhiyin Lin
----
File to support the ASL Glove!

The glove has 6 sensors: 5 flex sensors and 1 accelerometer / gyroscope
This file mainly deals with initialization, sensor communication, calibration, and detection.
 */


// minimum and maximum of two numbers
 #define max(a,b) \
   ({ a > b ? a : b; })
 #define min(a,b) \
   ({ a < b ? a : b; })

#include "mcp3008.h"
#include "printf.h"
#include "flex.h"
#include "timer.h"
#include "glove.h"
#include "LSM6DS33.h"

/* 
Function: constrain
------
@params: num - number to contrain to the range of @param min and @param max
@return: constrained number
 */
int constrain(int num, int min, int max){
    if (num > max){
        return max;
    }
    else if (num < min){
        return min;
    }
    else{
        return num;
    }
}

/* 
Function: map
------
Fits the int @param x to the output range given the input range through a linear map
input range: @param in_min to @param in_max
output range: @param out_min to @param out_max

@return -1 if minimum and maximum does not match or x is not within input range
@return the value after linear mapping
 */
float map(int x, int in_min, int in_max, int out_min, int out_max){
    // if inputs invalid
    if (in_max <= in_min || out_max <= out_min || x < in_min || x > in_max){
        return -1;
    }
    // linear map
    return ((float)(x - in_min)) * (out_max - out_min) / (in_max - in_min) + out_min;
}

/* 
Function: glove_init_min
------
Instructs users to calibrate minimum for the sensors (curl fingers).

Reads from flex sensor and finds the minimum value read for each sensor.
Stores the values read into the `glove` struct.
prints the calibration and parameters
 */
void glove_init_min(struct Glove* glove){
    printf("Begin calibrating min. Curl your fingers. You have five seconds.");
    // reads after 5 seconds
    timer_delay(5);
    // reads values as mininmum
    glove->sensorMin1 = read_flex(0);
    glove->sensorMin2 = read_flex(1);
    glove->sensorMin3 = read_flex(2);
    glove->sensorMin4 = read_flex(3);
    glove->sensorMin5 = read_flex(4);
    printf("Finish calibrating min.");
    printf("Mins: %d %d %d %d %d \n", glove->sensorMin1, glove->sensorMin2, glove->sensorMin3, glove->sensorMin4, glove->sensorMin5);
}

/* 
Function: glove_init_max
------
Instructs users to calibrate maximum for the sensors (straight fingers).

Reads from flex sensor and finds the maximum value read for each sensor.
Stores the values read into the `glove` struct.
prints the calibration and parameters
 */
void glove_init_max(struct Glove* glove){
    printf("Begin calibrating max. Put your fingers straight. You have five seconds.");
    // reads after 5 seconds
    timer_delay(5);
    // reads values as maximum
    glove->sensorMax1 = read_flex(0);
    glove->sensorMax2 = read_flex(1);
    glove->sensorMax3 = read_flex(2);
    glove->sensorMax4 = read_flex(3);
    glove->sensorMax5 = read_flex(4);
    printf("Finish calibrating max.");
    printf("Maxs: %d %d %d %d %d \n", glove->sensorMax1, glove->sensorMax2, glove->sensorMax3, glove->sensorMax4, glove->sensorMax5);
}

/* 
Function: glove_calculate
------
Checks if a finger is bent slightly by angle
 */
void glove_calculate(struct Glove* glove, int sec){
    short x, y, z;
    short max_x = 0, max_y = 0, max_z = 0, min_x = 0, min_y = 0, min_z = 0;
    for (int i = 0; i < 6; i++){
        // reads from the accelerometer to get the range of motion
        lsm6ds33_read_accelerometer(&x, &y, &z);
        if (i == 0){
            max_x = x;
            max_y = y;
            max_z = z;
            min_x = x;
            min_y = y;
            max_z = z;
        }
        else{
            max_x = max(max_x, x);
            max_y = max(max_y, y);
            max_z = max(max_z, z);
            min_x = min(min_x, x);
            min_y = min(min_y, y);
            min_z = min(min_z, z);
        }
        // delay a certain time to perform the next calculation
        timer_delay_ms((int)((sec*1000)/6));
    }
    // records the range in gap
    glove->gap = max(max(max_x - min_x, max_y - min_y), max_z - min_z);

    int FLEX_PIN1 = 0; // little finger
    int FLEX_PIN2 = 1; // ring finger
    int FLEX_PIN3 = 2; // middle finger
    int FLEX_PIN4 = 3; // index finger
    int FLEX_PIN5 = 4; // thumb

    // reads from the flex sensor
    int flexADC1 = read_flex(FLEX_PIN1);
    int flexADC2 = read_flex(FLEX_PIN2);
    int flexADC3 = read_flex(FLEX_PIN3);
    int flexADC4 = read_flex(FLEX_PIN4);
    int flexADC5 = read_flex(FLEX_PIN5);

    // constrains the flex sensor's readings to the minimum and maximum
    flexADC1 = constrain(flexADC1, glove->sensorMin1, glove->sensorMax1);
    flexADC2 = constrain(flexADC2, glove->sensorMin2, glove->sensorMax2);
    flexADC3 = constrain(flexADC3, glove->sensorMin3, glove->sensorMax3);
    flexADC4 = constrain(flexADC4, glove->sensorMin4, glove->sensorMax4);
    flexADC5 = constrain(flexADC5, glove->sensorMin5, glove->sensorMax5);

    // maps the readings to an angle between 0 and 90
    glove->angle1= 90 - map(flexADC1, glove->sensorMin1, glove->sensorMax1, 0, 90);
    glove->angle2= 90 - map(flexADC2, glove->sensorMin2, glove->sensorMax2, 0, 90);
    glove->angle3= 90 - map(flexADC3, glove->sensorMin3, glove->sensorMax3, 0, 90);
    glove->angle4= 90 - map(flexADC4, glove->sensorMin4, glove->sensorMax4, 0, 90);
    glove->angle5= 90 - map(flexADC5, glove->sensorMin5, glove->sensorMax5, 0, 90); 
    
}

/* 
Function: get_angle
-----
supports getting angle at the finger @param flex_channel in the number of seconds @param sec
reads from the glove @param glove
 */
int get_angle(int flex_channel, struct Glove* glove, int sec){
    if (flex_channel < 0 || flex_channel > 4)
    glove_calculate(glove, sec);
    if (flex_channel == 0) return glove->angle1;
    if (flex_channel == 1) return glove->angle2;
    if (flex_channel == 2) return glove->angle3;
    if (flex_channel == 3) return glove->angle4;
    else return glove->angle5;
}


/* 
Function: glove_read_char
------
@param glove: the struct for the glove
@param sec: number of seconds to read a character

contains the decision process to decide on the character for ASL.
 */
char glove_read_char(struct Glove* glove, int sec){
    glove_calculate(glove, sec);
    char c = '*';
    if(is_flexed(glove->angle1)&&
       is_flexed(glove->angle2)&&
       is_flexed(glove->angle3)&&
       is_flexed(glove->angle4)&&
       is_straight(glove->angle5)){
        c = 'A';
    }

    if(is_straight(glove->angle1)&&
       is_straight(glove->angle2)&&
       is_straight(glove->angle3)&&
       is_straight(glove->angle4)&&
       is_bent(glove->angle5)){
        c = 'B';
    }

    if((glove->angle1 >= 30) && (glove->angle1 <= 60)&&
       is_bent(glove->angle2)&&
       is_bent(glove->angle3)&&
       is_bent(glove->angle4)&&
       is_slight_bent(glove->angle5)){
        c = 'C';
    }

    if(is_bent(glove->angle1)&&
       is_bent(glove->angle2)&&
       is_bent(glove->angle3)&&
       is_straight(glove->angle4)&&
       is_slight_bent(glove->angle5)){
        c = 'D';
    }

    if(is_flexed(glove->angle1)&&
       is_flexed(glove->angle2)&&
       is_flexed(glove->angle3)&&
       is_flexed(glove->angle4)&&
       is_flexed(glove->angle5)){
        c = 'E';
    }

    if(is_straight(glove->angle1)&&
       is_straight(glove->angle2)&&
       is_straight(glove->angle3)&&
       is_bent(glove->angle4)&&
       is_slight_bent(glove->angle5)){
        c = 'F';
    }

    if(is_flexed(glove->angle1)&&
       is_flexed(glove->angle2)&&
       is_flexed(glove->angle3)&&
       is_straight(glove->angle4)&&
       is_slight_bent(glove->angle5)){
        c = 'G';
    }

    if(is_flexed(glove->angle1)&&
       is_flexed(glove->angle2)&&
       is_straight(glove->angle3)&&
       is_straight(glove->angle4)&&
       is_slight_bent(glove->angle5)){
        c = 'H';
    }

    if(is_straight(glove->angle1)&&
       is_flexed(glove->angle2)&&
       is_flexed(glove->angle3)&&
       is_flexed(glove->angle4)&&
       is_slight_bent(glove->angle5)){
        c = 'I';
    }
    
    if(glove->gap > 10000 &&
       is_straight(glove->angle1)&&
       is_flexed(glove->angle2)&&
       is_flexed(glove->angle3)&&
       is_flexed(glove->angle4)&&
       is_slight_bent(glove->angle5)){
        c = 'J';
    }

    if(is_flexed(glove->angle1)&&
       is_flexed(glove->angle2)&&
       is_straight(glove->angle3)&&
       is_straight(glove->angle4)&&
       is_straight(glove->angle5)){
        c = 'K';
    }

    if(is_flexed(glove->angle1)&&
       is_flexed(glove->angle2)&&
       is_flexed(glove->angle3)&&
       is_straight(glove->angle4)&&
       is_straight(glove->angle5)){
        c = 'L';
    }

    if((glove->angle1 >= 60) && (glove->angle1 <= 90)&&
       is_bent(glove->angle2)&&
       is_bent(glove->angle3)&&
       is_bent(glove->angle4)&&
       is_bent(glove->angle5)){
        c = 'M';
    }

    if(is_flexed(glove->angle1)&&
       is_flexed(glove->angle2)&&
       is_bent(glove->angle3)&&
       is_bent(glove->angle4)&&
       is_slight_bent(glove->angle5)){
        c = 'N';
    }

    if(is_bent(glove->angle1)&&
       is_bent(glove->angle2)&&
       is_bent(glove->angle3)&&
       is_bent(glove->angle4)&&
       is_straight(glove->angle5)){
        c = 'O';
    }

    if(is_bent(glove->angle1)&&
       is_bent(glove->angle2)&&
       is_straight(glove->angle3)&&
       is_straight(glove->angle4)&&
       is_straight(glove->angle5)){
        c = 'P';
    }

    if(is_bent(glove->angle1)&&
       is_bent(glove->angle2)&&
       is_bent(glove->angle3)&&
       is_straight(glove->angle4)&&
       is_straight(glove->angle5)){
        c = 'Q';
    }

    if(is_bent(glove->angle1)&&
       is_bent(glove->angle2)&&
       is_straight(glove->angle3)&&
       is_slight_bent(glove->angle4)&&
       is_slight_bent(glove->angle5)){
        c = 'R';
    }

    if(is_flexed(glove->angle1)&&
       is_flexed(glove->angle2)&&
       is_flexed(glove->angle3)&&
       is_flexed(glove->angle4)&&
       is_slight_bent(glove->angle5)){
        c = 'S';
    }

    if(is_flexed(glove->angle1)&&
       is_flexed(glove->angle2)&&
       is_flexed(glove->angle3)&&
       is_slight_bent(glove->angle4)&&
       is_slight_bent(glove->angle5)){
        c = 'T';
    }
  
    if(is_bent(glove->angle1)&&
       is_bent(glove->angle2)&&
       is_straight(glove->angle3)&&
       is_straight(glove->angle4)&&
       is_bent(glove->angle5)){
        c = 'U';
    }

    if(is_bent(glove->angle1)&&
       is_bent(glove->angle2)&&
       is_straight(glove->angle3)&&
       is_straight(glove->angle4)&&
       is_bent(glove->angle5)){
        c = 'V';
    } 

    if(is_bent(glove->angle1)&&
       is_straight(glove->angle2)&&
       is_straight(glove->angle3)&&
       is_straight(glove->angle4)&&
       is_bent(glove->angle5)){
        c = 'W';
    }

    if(is_flexed(glove->angle1)&&
       is_flexed(glove->angle2)&&
       is_flexed(glove->angle3)&&
       is_bent(glove->angle4)&&
       is_flexed(glove->angle5)){
        c = 'X';
    }

    if(is_straight(glove->angle1)&&
       (is_bent(glove->angle2) || is_flexed(glove->angle2)) &&
       (is_bent(glove->angle3) || is_flexed(glove->angle3))&&
       (is_bent(glove->angle4) || is_flexed(glove->angle4))&&
       is_straight(glove->angle5)){
        c = 'Y';
    }

    if(glove->gap > 10000 && 
       is_bent(glove->angle1)&&
       is_bent(glove->angle2)&&
       is_bent(glove->angle3)&&
       is_straight(glove->angle4)&&
       is_slight_bent(glove->angle5)){
        c = 'Z';
    }

    // Special Characters: space 
    if(is_straight(glove->angle1)&&
       (is_bent(glove->angle2) || is_flexed(glove->angle2))&&
       (is_bent(glove->angle3) || is_flexed(glove->angle3))&&
       is_straight(glove->angle4)&&
       is_straight(glove->angle5)){
        c = '_';
    }

    // Special Characters: backspace 
    if(is_straight(glove->angle1)&&
       is_straight(glove->angle2)&&
       is_straight(glove->angle3)&&
       is_straight(glove->angle4)&&
       is_straight(glove->angle5)){
        c = '\b';
    }
    return c;
}

