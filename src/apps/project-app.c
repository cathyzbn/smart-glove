#include "printf.h"
#include "uart.h"
#include "timer.h"

#include "flex.h"
#include "mcp3008.h"
#include "i2c_up.h"
#include "LSM6DS33.h"

#include "glove.h"

// TODO: i2c_up.c error: bitwise comparison always evaluates to false
//    77 |         while((*i2c.status & I2C_TXD)==1) {
void test_flex(int x){
    mcp3008_init();

    while(1){
        printf("%d\n", read_flex(x));
        timer_delay(1);
    }
}

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

//TODO: delete print in LSM, i2c.c
struct Cursor{ 
    int x;
};

void test_glove(void){
    mcp3008_init();
    printf("Begin initialization. \n");
    struct Glove glove;
    glove_init_min(&glove);
    glove_init_max(&glove);

    printf("End initialization. \n");
    char prevChar = '0'; // a placeholder \neq ' '
    struct Cursor cursor;
    // cursor.x = 0;
    int time = 0;

    while (true){
        timer_delay(2);

        printf("Time %d\n", time);
        time ++;

        char c = glove_read_char(&glove); // TODO: check name
        printf("%c\n", c); // TODO: could uart output faster, but need initialization if so
        // glove_reset(); // TODO: check name
        // if (c == '\b'){
        //     if (cursor.x >= 1){
        //         printf("%c", '\b');
        //         printf("%c", ' ');
        //         printf("%c", '\b');
        //         cursor.x --;
        //     }
        // }
        // else if (c == ' '){
        //     if (prevChar != ' '){
        //         printf("%c", ' '); // TODO: could uart output faster, but need initialization if so
        //     }
        // }
        // else {
        //     printf("%c", c); // TODO: could uart output faster, but need initialization if so
        // }
    }
}

void main(void)
{
    timer_init();
    uart_init();
    printf("Hello, world!\n");
    
    // test_flex(0);
    // test_accelero();

    test_glove();

    uart_putchar(EOT);
}
