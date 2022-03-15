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
        glove->sensorMax4=flexADC4;
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

    if(((angle1>=70)&&(angle1<=82))&&((angle2>=77)&&(angle2<=95))&&((angle3>=70)&&(angle3<=86))&&((angle4>=73)&&(angle4<=85))&&((angle5>=0)&&(angle5<=45))){
        c = 'A';
    }
    if(((angle1>=0)&&(angle1<=10))&&((angle2>=0)&&(angle2<=10))&&((angle3>=0)&&(angle3<=12))&&((angle4>=0)&&(angle4<=10))&&((angle5>=65)&&(angle5<=80))){
        c = 'B';
    }
    if(((angle1>=40)&&(angle1<=72))&&((angle2>=50)&&(angle2<=90))&&((angle3>=51)&&(angle3<=75))&&((angle4>=42)&&(angle4<=66))&&((angle5>=34)&&(angle5<=50))){
        c = 'C';
    }
    // if(((angle1>=50)&&(angle1<=72))&&((angle2>=45)&&(angle2<=90))&&((angle3>=35)&&(angle3<=75))&&((angle4>=0)&&(angle4<=10))&&((angle5>=45)&&(angle5<=80))&&!(((xadc>=412)&&(xadc<=418))&&((yadc>=340)&&(yadc<=360)))){
    if(((angle1>=50)&&(angle1<=72))&&((angle2>=45)&&(angle2<=90))&&((angle3>=35)&&(angle3<=75))&&((angle4>=0)&&(angle4<=10))&&((angle5>=45)&&(angle5<=80))){
        c = 'D';
    }
    if(((angle1>=68)&&(angle1<=88))&&((angle2>=68)&&(angle2<=90))&&((angle3>=50)&&(angle3<=80))&&((angle4>=54)&&(angle4<=80))&&((angle5>=58)&&(angle5<=88))){
        c = 'E';
    }
    if(((angle1>=0)&&(angle1<=10))&&((angle2>=0)&&(angle2<=10))&&((angle3>=0)&&(angle3<=10))&&((angle4>=15)&&(angle4<=45))&&((angle5>=34)&&(angle5<=65))){
        c = 'F';
    }
    // if(((angle1>=75)&&(angle1<=90))&&((angle2>=75)&&(angle2<=90))&&((angle3>=65)&&(angle3<=90))&&((angle4>=0)&&(angle4<=15))&&((angle5>=0)&&(angle5<=30))&&(((xadc>=400)&&(xadc<=420))&&((yadc>=340)&&(yadc<=360)))){
    if(((angle1>=75)&&(angle1<=90))&&((angle2>=75)&&(angle2<=90))&&((angle3>=65)&&(angle3<=90))&&((angle4>=0)&&(angle4<=15))&&((angle5>=0)&&(angle5<=30))){
        c = 'G';
    }
    // if(((angle1>=70)&&(angle1<=85))&&((angle2>=75)&&(angle2<=90))&&((angle3>=0)&&(angle3<=10))&&((angle4>=0)&&(angle4<=10))&&((angle5>=50)&&(angle5<=65))&&!(((xadc>=410)&&(xadc<=420))&&((yadc>=368)&&(yadc<=380)))){
    if(((angle1>=70)&&(angle1<=85))&&((angle2>=75)&&(angle2<=90))&&((angle3>=0)&&(angle3<=10))&&((angle4>=0)&&(angle4<=10))&&((angle5>=50)&&(angle5<=65))){
        c = 'H';
    }    
    // if(((angle1>=0)&&(angle1<=10))&&((angle2>=50)&&(angle2<=70))&&((angle3>=50)&&(angle3<=70))&&((angle4>=50)&&(angle4<=70))&&((angle5>=50)&&(angle5<=85)&&((xadc>=410)&&(xadc<=420))&&((yadc>=330)&&(yadc<=370)))){
    if(((angle1>=0)&&(angle1<=10))&&((angle2>=50)&&(angle2<=70))&&((angle3>=50)&&(angle3<=70))&&((angle4>=50)&&(angle4<=70))&&((angle5>=50)&&(angle5<=85))){
        c = 'I';
    }    
    // if(((angle1>=0)&&(angle1<=10))&&((angle2>=50)&&(angle2<=70))&&((angle3>=50)&&(angle3<=70))&&((angle4>=50)&&(angle4<=70))&&((angle5>=50)&&(angle5<=85))&&(!((xadc>=410)&&(xadc<=420))&&((yadc>=355)&&(yadc<=370)))){
    if(((angle1>=0)&&(angle1<=10))&&((angle2>=50)&&(angle2<=70))&&((angle3>=50)&&(angle3<=70))&&((angle4>=50)&&(angle4<=70))&&((angle5>=50)&&(angle5<=85))){
        c = 'J';
    }    
    // if(((angle1>=60)&&(angle1<=75))&&((angle2>=60)&&(angle2<=85))&&((angle3>=0)&&(angle3<=10))&&((angle4>=0)&&(angle4<=15))&&((angle5>=30)&&(angle5<=55))&&(((xadc>=404)&&(xadc<=415))&&((yadc>=368)&&(yadc<=380)))){
    if(((angle1>=60)&&(angle1<=75))&&((angle2>=60)&&(angle2<=85))&&((angle3>=0)&&(angle3<=10))&&((angle4>=0)&&(angle4<=15))&&((angle5>=30)&&(angle5<=55))){
        c = 'K';
    }
    // if(((angle1>=75)&&(angle1<=90))&&((angle2>=75)&&(angle2<=90))&&((angle3>=70)&&(angle3<=90))&&((angle4>=0)&&(angle4<=15))&&((angle5>=0)&&(angle5<=30))&&(((xadc>=390)&&(xadc<=405))&&((yadc>=360)&&(yadc<=380)))&&!((xadc>=270)&&(xadc<=300))&&((yadc>=360)&&(yadc<=390))){
    if(((angle1>=75)&&(angle1<=90))&&((angle2>=75)&&(angle2<=90))&&((angle3>=70)&&(angle3<=90))&&((angle4>=0)&&(angle4<=15))&&((angle5>=0)&&(angle5<=30))){
        c = 'L';
    }    
    if(((angle1>=40)&&(angle1<=61))&&((angle2>=72)&&(angle2<=84))&&((angle3>=45)&&(angle3<=65))&&((angle4>=62)&&(angle4<=75))&&((angle5>=65)&&(angle5<=86))){
        c = 'M';
    }    
    // if(((angle1>=54)&&(angle1<=70))&&((angle2>=50)&&(angle2<=61))&&((angle3>=48)&&(angle3<=66))&&((angle4>=60)&&(angle4<=76))&&((angle5>=50)&&(angle5<=65))&&(((xadc>=400)&&(xadc<=435))&&((yadc>=350)&&(yadc<=390)))){
    if(((angle1>=54)&&(angle1<=70))&&((angle2>=50)&&(angle2<=61))&&((angle3>=48)&&(angle3<=66))&&((angle4>=60)&&(angle4<=76))&&((angle5>=50)&&(angle5<=65))){
        c = 'N';
    }    
    if(((angle1>=68)&&(angle1<=88))&&((angle2>=68)&&(angle2<=90))&&((angle3>=50)&&(angle3<=80))&&((angle4>=54)&&(angle4<=80))&&((angle5>=0)&&(angle5<=30))){
        c = 'O';
    }    
    // if(((angle1>=60)&&(angle1<=75))&&((angle2>=60)&&(angle2<=85))&&((angle3>=0)&&(angle3<=10))&&((angle4>=0)&&(angle4<=15))&&((angle5>=30)&&(angle5<=55))&&(((xadc>=270)&&(xadc<=290))&&((yadc>=360)&&(yadc<=380)))){
    if(((angle1>=60)&&(angle1<=75))&&((angle2>=60)&&(angle2<=85))&&((angle3>=0)&&(angle3<=10))&&((angle4>=0)&&(angle4<=15))&&((angle5>=30)&&(angle5<=55))){
        c = 'P';
    }    
    // if(((angle1>=75)&&(angle1<=90))&&((angle2>=75)&&(angle2<=90))&&((angle3>=65)&&(angle3<=90))&&((angle4>=0)&&(angle4<=15))&&((angle5>=0)&&(angle5<=30))&&(((xadc>=270)&&(xadc<=300))&&((yadc>=360)&&(yadc<=390)))){
    if(((angle1>=75)&&(angle1<=90))&&((angle2>=75)&&(angle2<=90))&&((angle3>=65)&&(angle3<=90))&&((angle4>=0)&&(angle4<=15))&&((angle5>=0)&&(angle5<=30))){
        c = 'Q';
    }    
    // if(((angle1>=40)&&(angle1<=72))&&((angle2>=45)&&(angle2<=90))&&((angle3>=20)&&(angle3<=45))&&((angle4>=0)&&(angle4<=10))&&((angle5>=45)&&(angle5<=80))&&(((xadc>=412)&&(xadc<=418))&&((yadc>=340)&&(yadc<=360)))){
    if(((angle1>=40)&&(angle1<=72))&&((angle2>=45)&&(angle2<=90))&&((angle3>=20)&&(angle3<=45))&&((angle4>=0)&&(angle4<=10))&&((angle5>=45)&&(angle5<=80))){
        c = 'R';
    }
    if(((angle1>=70)&&(angle1<=90))&&((angle2>=80)&&(angle2<=90))&&((angle3>=80)&&(angle3<=90))&&((angle4>=80)&&(angle4<=90))&&((angle5>=60)&&(angle5<=80))){
        c = 'S';
    }
    // if(((angle1>=40)&&(angle1<=61))&&((angle2>=72)&&(angle2<=84))&&((angle3>=45)&&(angle3<=65))&&((angle4>=44)&&(angle4<=63))&&((angle5>=65)&&(angle5<=86))&&(digitalRead(6)==HIGH)){
    if(((angle1>=40)&&(angle1<=61))&&((angle2>=72)&&(angle2<=84))&&((angle3>=45)&&(angle3<=65))&&((angle4>=44)&&(angle4<=63))&&((angle5>=65)&&(angle5<=86))){
        c = 'T';
    }    
    if(((angle1>=70)&&(angle1<=90))&&((angle2>=80)&&(angle2<=90))&&((angle3>=0)&&(angle3<=10))&&((angle4>=0)&&(angle4<=10))&&((angle5>=60)&&(angle5<=80))){
        c = 'U';
    }    
    // if(((angle1>=70)&&(angle1<=90))&&((angle2>=80)&&(angle2<=90))&&((angle3>=0)&&(angle3<=10))&&((angle4>=0)&&(angle4<=10))&&((angle5>=60)&&(angle5<=80))&&(digitalRead(6)==HIGH)) {
    if(((angle1>=70)&&(angle1<=90))&&((angle2>=80)&&(angle2<=90))&&((angle3>=0)&&(angle3<=10))&&((angle4>=0)&&(angle4<=10))&&((angle5>=60)&&(angle5<=80))) {
        c = 'V';
    }    
    if(((angle1>=70)&&(angle1<=90))&&((angle2>=0)&&(angle2<=10))&&((angle3>=0)&&(angle3<=10))&&((angle4>=0)&&(angle4<=10))&&((angle5>=60)&&(angle5<=80))){
        c = 'W';
    }    
    if(((angle1>=50)&&(angle1<=72))&&((angle2>=45)&&(angle2<=90))&&((angle3>=35)&&(angle3<=75))&&((angle4>=80)&&(angle4<=89))&&((angle5>=45)&&(angle5<=80))){//&&!(((xadc>=412)&&(xadc<=418))&&((yadc>=340)&&(yadc<=360))))
        c = 'X';
    }
    if(((angle1>=0)&&(angle1<=10))&&((angle2>=70)&&(angle2<=90))&&((angle3>=60)&&(angle3<=80))&&((angle4>=80)&&(angle4<=90))&&((angle5>=15)&&(angle5<=35))){
        c = 'Y';
    }
    // if(((angle1>=50)&&(angle1<=72))&&((angle2>=45)&&(angle2<=90))&&((angle3>=35)&&(angle3<=75))&&((angle4>=0)&&(angle4<=10))&&((angle5>=45)&&(angle5<=80))&&(((xadc>=412)&&(xadc<=418))&&((yadc>=340)&&(yadc<=360)))){
    if(((angle1>=50)&&(angle1<=72))&&((angle2>=45)&&(angle2<=90))&&((angle3>=35)&&(angle3<=75))&&((angle4>=0)&&(angle4<=10))&&((angle5>=45)&&(angle5<=80))){
        c = 'Z';
    }
    // TODO: add backspace, space 
    return c;
}

