#include "mcp3008.h"
#include "printf.h"
#include "flex.h"

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

enum {
    STAIGHT = 0,
    SLIGHTLY_BENT = 1,
    BENT = 2,
    FLEX = 3
};




void glove_init_min();
void glove_init_max();
char glove_read_char();
