#include "printf.h"
#include "uart.h"
#include "teacher.h"
#include "glove_console.h"

void main(void)
{
    uart_init();
    
    // glove typing console
    glove_console();
    
    // teacher module
    // teacher();
    
    uart_putchar(EOT);
}
