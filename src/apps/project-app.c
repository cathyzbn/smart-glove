#include "printf.h"
#include "uart.h"
#include "flex.h"
#include "mcp3008.h"
#include "timer.h"


void test_flex(void){
    mcp3008_init();

    while(1){
        printf("%d", read_flex(0));
        timer_delay(1);
    }
}

void main(void)
{
    uart_init();
    printf("Hello, world!\n");
    
    // test_flex();
    

    uart_putchar(EOT);
}
