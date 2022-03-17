/* 
File: project-tests
----
Tester for the project. Includes tests for flex sensor and accelerometer.
 */

#include "printf.h"
#include "uart.h"
#include "timer.h"

#include "flex.h"
#include "mcp3008.h"
#include "i2c_up.h"
#include "LSM6DS33.h"

#include "glove.h"
#include "console_up.h"

/* 
Function: test_flex
--------
Takes in an input, x, of the channel for the flex sensor. Continuously prints
the number that the ADC detects.
 */
void test_flex(int x){
    mcp3008_init();

    while(1){
        printf("%d\n", read_flex(x));
        timer_delay(1);
    }
}

/*
Function: test_accelero
-------
Reads from the accelerometer and outputs continuously
 */
void test_accelero(void){
    i2c_init();
    lsm6ds33_init();

    while(1) { 
        short x, y, z;
        lsm6ds33_read_accelerometer(&x, &y, &z);
        printf("current position, x:%d, y:%d, z:%d\n", x, y, z);
        
        // 16384 is 1g (1g == 1000mg)
        timer_delay_ms(200);
	}
}

/* 
Function: test_gyro
-------
Reads from the gyroscope and outputs continuously
 */
void test_gyro(void){
    i2c_init();
    lsm6ds33_init();

    while(1) { 
        short x, y, z;
        lsm6ds33_read_gyroscope(&x, &y, &z);
        // 16384 is 1g (1g == 1000mg)
        timer_delay_ms(200);
	}
}

void main(void)
{
    timer_init();
    uart_init();
    printf("Hello, world!1\n");
    
    test_flex(0);
    test_accelero();

    uart_putchar(EOT);
}
