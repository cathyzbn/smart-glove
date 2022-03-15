#include "printf.h"
#include "uart.h"
#include "timer.h"

#include "flex.h"
#include "mcp3008.h"
#include "i2c_up.h"
#include "LSM6DS33.h"

#include "glove.h"
#include "console_up.h"

// TODO: i2c_up.c error: bitwise comparison always evaluates to false
//    77 |         while((*i2c.status & I2C_TXD)==1) {
static unsigned int nrows = 20;
static unsigned int ncols = 50;

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
void test_glove(void){
    i2c_init();
    lsm6ds33_init();
    mcp3008_init();
    struct Glove glove;

    printf("Begin initialization. \n");
    glove_init_min(&glove);
    glove_init_max(&glove);
    printf("End initialization. \n");

    char prevChar = '0'; // a placeholder \neq ' '
    int count = 0;

    console_init(nrows, ncols, GL_WHITE, GL_INDIGO);

    while (true){
        // printf("Count %d\n", count);
        count ++;

        char c = glove_read_char(&glove, 1); 
        if (c == '*'){
            continue;
        }
        if (c == '\b'){
            // if (console.cursor.x < gl_get_char_width()){ // backspace across lines
            //     if (console.cursor.y >= line_height){ 
            //         // shift cursor
            //         console.cursor.x = (console.ncols - 1) * gl_get_char_width();
            //         console.cursor.y -= line_height;
            //         // draw a whitespace (i.e. rectangular of background color)
            //         gl_draw_rect(console.cursor.x, console.cursor.y, gl_get_char_width(), line_height, console.bcolor);
            //         gl_swap_buffer();
            //         gl_draw_rect(console.cursor.x, console.cursor.y, gl_get_char_width(), line_height, console.bcolor);
            //     }
            // }
            // else{ // backspace in-line
            //     // shift cursor
            //     console.cursor.x -= gl_get_char_width();
            //     // draw a whitespace (i.e. rectangular of background color)
            //     gl_draw_rect(console.cursor.x, console.cursor.y, gl_get_char_width(), line_height, console.bcolor);
            //     gl_swap_buffer();
            //     gl_draw_rect(console.cursor.x, console.cursor.y, gl_get_char_width(), line_height, console.bcolor);
            // }
            console_printf("%c", '\b');
            console_printf("%c", ' ');
        }
        console_printf("%c", c);

        // if (c == '\b'){
        //     if (cursor.x >= 1){
        //         // printf("%c", '\b');
        //         // printf("%c", ' ');
        //         // printf("%c", '\b');
        //         cursor.x --;
        //     }
        // }
        // else if (c == ' '){
        //     if (prevChar != ' '){
        //         printf("%c", ' '); 
        //     }
        // }
        // else {
        //     printf("%c", c); 
        // }
    }
}

void main(void)
{
    timer_init();
    uart_init();
    printf("Hello, world!1\n");
    
    // test_flex(0);
    // test_accelero();

    test_glove();

    uart_putchar(EOT);
}
