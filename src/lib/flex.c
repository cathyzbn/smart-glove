#include "mcp3008.h"
#include "printf.h"
#include "flex.h"

int valid_flex_channel(unsigned int flex_channel){
    return flex_channel<5 && flex_channel >=0;
}

int read_flex(unsigned int flex_channel){
    if (!valid_flex_channel(flex_channel)){
        return -1;
    }
    
    return mcp3008_read(flex_channel);

}