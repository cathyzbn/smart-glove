#include "printf.h"
#include "uart.h"
#include "teacher.h"

void main(void)
{
    uart_init();
    
    teacher();
    
    uart_putchar(EOT);
}
