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

};
void glove_init_min();
void glove_init_max();
char glove_read_char();
