#include "mcp3008.h"
#include "printf.h"
#include "flex.h"
#include "timer.h"
#include "glove.h"

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

float map(int x, int in_min, int in_max, int out_min, int out_max){
    if (in_max == in_min){
        printf("in_max can not equal to in_min");
        return -1;
    }
    return ((float)(x - in_min)) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void glove_init_min(struct Glove* glove){
    printf("Begin calibrating min. Curl your fingers. You have five seconds.");
    timer_delay(5);
    glove->sensorMin1 = read_flex(0);
    glove->sensorMin2 = read_flex(1);
    glove->sensorMin3 = read_flex(2);
    glove->sensorMin4 = read_flex(3);
    glove->sensorMin5 = read_flex(4);
    printf("Finish calibrating min.");
    printf("Mins: %d %d %d %d %d \n", glove->sensorMin1, glove->sensorMin2, glove->sensorMin3, glove->sensorMin4, glove->sensorMin5);
}

void glove_init_max(struct Glove* glove){
    printf("Begin calibrating max. Put your fingers straight. You have five seconds.");
    timer_delay(5);
    glove->sensorMax1 = read_flex(0);
    glove->sensorMax2 = read_flex(1);
    glove->sensorMax3 = read_flex(2);
    glove->sensorMax4 = read_flex(3);
    glove->sensorMax5 = read_flex(4);
    printf("Finish calibrating max.");
    printf("Maxs: %d %d %d %d %d \n", glove->sensorMax1, glove->sensorMax2, glove->sensorMax3, glove->sensorMax4, glove->sensorMax5);
}

int is_flexed(int angle){
    return (angle >= 70) && (angle <= 90);
}

int is_straight(int angle){
    return (angle >= 0) && (angle <= 20); 
}

int is_bent(int angle){
    return (angle >= 30) && (angle <= 70);
}

int is_slight_bent(int angle){
    return (angle>=15) && (angle <= 40);
}

char glove_read_char(struct Glove* glove){
    char c = '0';

    //variable initializtion
    // int xpin = A5;
    // int xadc = 0;
    // int xmax = 0;
    // int xmin = 1023;

    // int ypin = A6;
    // int yadc = 0;
    // int ymax = 0;
    // int ymin = 1023;

    int FLEX_PIN1 = 0; // channel 0
    // int flexADC1 = 0; 
    // int sensorMin1 = 400; 
    // int sensorMax1 = 800;

    int FLEX_PIN2 = 1; // channel 1
    // int flexADC2 = 0; 
    // int sensorMin2 = 400; 
    // int sensorMax2 = 800;

    int FLEX_PIN3 = 2; 
    // int flexADC3 = 0; 
    // int sensorMin3 = 400; 
    // int sensorMax3 = 800;

    int FLEX_PIN4 = 3; 
    // int flexADC4 = 0; 
    // int sensorMin4 = 400; 
    // int sensorMax4 = 800;

    int FLEX_PIN5 = 4; 
    // int flexADC5 = 0; 
    // int sensorMin5 = 400; 
    // int sensorMax5 = 800;

// CALIBRATION: NOT NEEDED, recalculate range 0-1023 to reasonable range, might need rework 
    // int flexADC1 = read_flex(0);
    // int flexADC2 = read_flex(1);
    // int flexADC3 = read_flex(2);
    // int flexADC4 = read_flex(3);
    // int flexADC5 = read_flex(4);

    int flexADC1 = read_flex(FLEX_PIN1);
    int flexADC2 = read_flex(FLEX_PIN2);
    int flexADC3 = read_flex(FLEX_PIN3);
    int flexADC4 = read_flex(FLEX_PIN4);
    int flexADC5 = read_flex(FLEX_PIN5);
    printf("Flex Raw: %d %d %d %d %d\n", (int) flexADC1, (int) flexADC2, (int) flexADC3, (int) flexADC4, (int) flexADC5);

    if(flexADC1<glove->sensorMin1)
    {
        glove->sensorMin1=flexADC1;
    }
    if(flexADC1>glove->sensorMax1)
    {
        glove->sensorMax1=flexADC1;
    }

    if(flexADC2<glove->sensorMin2)
    {
        glove->sensorMin2=flexADC2;
    }
    if(flexADC2>glove->sensorMax2)
    {
        glove->sensorMax2=flexADC2;
    }

    if(flexADC3<glove->sensorMin3)
    {
        glove->sensorMin3=flexADC3;
    }
    if(flexADC3>glove->sensorMax3)
    {
        glove->sensorMax3=flexADC3;
    }

    if(flexADC5<glove->sensorMin5)
    {
        glove->sensorMin5=flexADC5;
    }
    if(flexADC5>glove->sensorMax5)
    {
        glove->sensorMax5=flexADC5;
    }

    if(flexADC4<glove->sensorMin4)
    {
        glove->sensorMin4=flexADC4;
    }
    if(flexADC4>glove->sensorMax4)
    {
        glove->sensorMax4=flexADC4;
    }

    flexADC1 = constrain(flexADC1, glove->sensorMin1, glove->sensorMax1);
    flexADC2 = constrain(flexADC2, glove->sensorMin2, glove->sensorMax2);
    flexADC3 = constrain(flexADC3, glove->sensorMin3, glove->sensorMax3);
    flexADC4 = constrain(flexADC4, glove->sensorMin4, glove->sensorMax4);
    flexADC5 = constrain(flexADC5, glove->sensorMin5, glove->sensorMax5);
    printf("Flex Constrain: %d %d %d %d %d\n", (int) flexADC1, (int) flexADC2, (int) flexADC3, (int) flexADC4, (int) flexADC5);

    float angle1= 90 - map(flexADC1, glove->sensorMin1, glove->sensorMax1, 0, 90);
    float angle2= 90 - map(flexADC2, glove->sensorMin2, glove->sensorMax2, 0, 90);
    float angle3= 90 - map(flexADC3, glove->sensorMin3, glove->sensorMax3, 0, 90);
    float angle4= 90 - map(flexADC4, glove->sensorMin4, glove->sensorMax4, 0, 90);
    float angle5= 90 - map(flexADC5, glove->sensorMin5, glove->sensorMax5, 0, 90); 

    printf("Angles: %d %d %d %d %d\n", (int) angle1, (int) angle2, (int) angle3, (int) angle4, (int) angle5);

    // xadc = analogRead(xpin);
    // yadc = analogRead(ypin);

    if(is_flexed(angle1)&&
       is_flexed(angle2)&&
       is_flexed(angle3)&&
       is_flexed(angle4)&&
       is_straight(angle5)){
        c = 'A';
    }

    if(is_straight(angle1)&&
       is_straight(angle2)&&
       is_straight(angle3)&&
       is_straight(angle4)&&
       (is_bent(angle5) || is_straight(angle5))){
        c = 'B';
    }

    // if(is_bent(angle1)&&
    if((angle1 >= 30) && (angle1 <= 60)&&
       is_bent(angle2)&&
       is_bent(angle3)&&
       is_bent(angle4)&&
       is_slight_bent(angle5)){
        c = 'C';
    }

    if(is_bent(angle1)&&
       is_bent(angle2)&&
       is_bent(angle3)&&
       is_straight(angle4)&&
       is_slight_bent(angle5)){
        c = 'D';
    }

    if(is_flexed(angle1)&&
       is_flexed(angle2)&&
       is_flexed(angle3)&&
       is_flexed(angle4)&&
       is_flexed(angle5)){
        c = 'E';
    }

    if(is_straight(angle1)&&
       is_straight(angle2)&&
       is_straight(angle3)&&
       is_bent(angle4)&&
       is_slight_bent(angle5)){
        c = 'F';
    }

    if(is_flexed(angle1)&&
       is_flexed(angle2)&&
       is_flexed(angle3)&&
       is_straight(angle4)&&
       is_slight_bent(angle5)){
        c = 'G';
    }

    if(is_flexed(angle1)&&
       is_flexed(angle2)&&
       is_straight(angle3)&&
       is_straight(angle4)&&
       is_slight_bent(angle5)){
        c = 'H';
    }

    if(is_straight(angle1)&&
       is_flexed(angle2)&&
       is_flexed(angle3)&&
       is_flexed(angle4)&&
       is_slight_bent(angle5)){
        c = 'I';
    }
    
    if(is_straight(angle1)&&
       is_flexed(angle2)&&
       is_flexed(angle3)&&
       is_flexed(angle4)&&
       is_slight_bent(angle5)){
        c = 'J';
    } // TODO: add accelerometer

    if(is_flexed(angle1)&&
       is_flexed(angle2)&&
       is_straight(angle3)&&
       is_straight(angle4)&&
       is_straight(angle5)){
        c = 'K';
    }

    if(is_flexed(angle1)&&
       is_flexed(angle2)&&
       is_flexed(angle3)&&
       is_straight(angle4)&&
       is_straight(angle5)){
        c = 'L';
    }

    if((angle1 >= 60) && (angle1 <= 90)&&
       is_bent(angle2)&&
       is_bent(angle3)&&
       is_bent(angle4)&&
       is_bent(angle5)){
        c = 'M';
    }

    if(is_flexed(angle1)&&
       is_flexed(angle2)&&
       is_bent(angle3)&&
       is_bent(angle4)&&
       is_slight_bent(angle5)){
        c = 'N';
    }

    if(is_bent(angle1)&&
       is_bent(angle2)&&
       is_bent(angle3)&&
       is_bent(angle4)&&
       is_straight(angle5)){
        c = 'O';
    }

    if(is_bent(angle1)&&
       is_bent(angle2)&&
       is_straight(angle3)&&
       is_straight(angle4)&&
       is_straight(angle5)){
        c = 'P';
    }

    if(is_bent(angle1)&&
       is_bent(angle2)&&
       is_bent(angle3)&&
       is_straight(angle4)&&
       is_straight(angle5)){
        c = 'Q';
    }

    if(is_bent(angle1)&&
       is_bent(angle2)&&
       is_straight(angle3)&&
       is_slight_bent(angle4)&&
       is_slight_bent(angle5)){
        c = 'R';
    }

    if(is_flexed(angle1)&&
       is_flexed(angle2)&&
       is_flexed(angle3)&&
       is_flexed(angle4)&&
       is_slight_bent(angle5)){
        c = 'S';
    }

    if(is_flexed(angle1)&&
       is_flexed(angle2)&&
       is_flexed(angle3)&&
       is_slight_bent(angle4)&&
       is_slight_bent(angle5)){
        c = 'T';
    }
  
    if(is_bent(angle1)&&
       is_bent(angle2)&&
       is_straight(angle3)&&
       is_straight(angle4)&&
       is_bent(angle5)){
        c = 'U';
    }

    if(is_bent(angle1)&&
       is_bent(angle2)&&
       is_straight(angle3)&&
       is_straight(angle4)&&
       is_bent(angle5)){
        c = 'V';
    } // TODO: distinguish U, V

    if(is_bent(angle1)&&
       is_straight(angle2)&&
       is_straight(angle3)&&
       is_straight(angle4)&&
       is_bent(angle5)){
        c = 'W';
    }

    if(is_flexed(angle1)&&
       is_flexed(angle2)&&
       is_flexed(angle3)&&
       is_bent(angle4)&&
       is_flexed(angle5)){
        c = 'X';
    }

    if(is_straight(angle1)&&
       (is_bent(angle2) || is_flexed(angle2)) &&
       (is_bent(angle3) || is_flexed(angle3))&&
       (is_bent(angle4 || is_flexed(angle4))&&
       is_straight(angle5)){
        c = 'Y';
    }

    if(is_bent(angle1)&&
       is_bent(angle2)&&
       is_bent(angle3)&&
       is_straight(angle4)&&
       is_slight_bent(angle5)){
        c = 'Z';
    } // TODO: add accelerometer

    // TODO: add backspace, space 
    return c;
}

