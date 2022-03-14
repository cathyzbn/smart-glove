
#include "printf.h"
#include "i2c_up.h"
#include "LSM6DS33.h"

int read_accel(){
    if (!valid_flex_channel(flex_channel)){
        return -1;
    }
    
    return mcp3008_read(flex_channel);
}