#include "printf.h"
#include "uart.h"
#include "timer.h"

#include "flex.h"
#include "mcp3008.h"
#include "i2c_up.h"
#include "LSM6DS33.h"

// TODO: i2c_up.c error: bitwise comparison always evaluates to false
//    77 |         while((*i2c.status & I2C_TXD)==1) {
void test_flex(void){
    mcp3008_init();

    while(1){
        printf("%d", read_flex(0));
        timer_delay(1);
    }
}

void test_accelero(void){
    i2c_init();
    lsm6ds33_init();

    while(1) { 
        short x, y, z;
        lsm6ds33_read_accelerometer(&x, &y, &z);
        // 16384 is 1g (1g == 1000mg)
        timer_delay_ms(200);
	}

}

//TODO: delete print in LSM, i2c.c


void main(void)
{
    timer_init();
    uart_init();
    printf("Hello, world!\n");
    
    // test_flex();
    test_accelero();
    

    uart_putchar(EOT);
}
