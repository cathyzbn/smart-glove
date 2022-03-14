// #include "gl.h"
// #include "gpio.h"
// #include "gpio_extra.h"
// #include "gpio_interrupts.h"
// #include "interrupts.h"
// #include "printf.h"
// #include "ringbuffer.h"
// #include "timer.h"
// #include "uart.h"

#include "glove.h"
#include "printf.h"
#include "timer.h"
// #include "uart.h"

// static const int BUTTON = GPIO_PIN20;
// static volatile int gCount = 0;

// void wait_for_click(void) {
//     // TODO: implement this function
//     while(gpio_read(BUTTON) == 1);
//     gCount++;
//     printf("Click!");
// }

// void redraw(int nclicks) {
//     static int nredraw = -1;
//     // count number of redraws, alternate bg color on each redraw
//     color_t bg = nredraw++ % 2 ? GL_AMBER : GL_BLUE;

//     gl_clear(GL_BLACK);
//     char buf[100];
//     snprintf(buf, sizeof(buf), "Click count = %d (redraw #%d)", nclicks, nredraw);
//     gl_draw_string(0, 0, buf, GL_WHITE);
//     for (int y = gl_get_char_height(); y < gl_get_height(); y++) {
//         for (int x = 0; x < gl_get_width(); x++) {
//             gl_draw_pixel(x, y, bg);
//         }
//     }
// }

// void handle_click(unsigned int pc, rb_t *aux_data){
//     rb_enqueue(aux_data, ++gCount);
//     // gCount++;
//     // printf("%s\n", (char*)aux_data);
//     gpio_clear_event(BUTTON);
// }

// void main(void) {
//     gpio_init();
//     uart_init();
//     gl_init(600, 400, GL_SINGLEBUFFER);

//     // Step 3
//     interrupts_init();
//     interrupts_global_enable();

//     // Step 2
//     gpio_interrupts_init();
//     rb_t *rb = rb_new();

//     // interrupts_register_handler(INTERRUPTS_GPIO3, handle_click, rb);
//     gpio_interrupts_register_handler(BUTTON, handle_click, rb);
//     // interrupts_register_handler(INTERRUPTS_GPIO3, handle_click, (void *)"Zhiyin Lin has interrupt mojo");
//     gpio_interrupts_enable();

//     // configure button
//     gpio_set_input(BUTTON);
//     gpio_set_pullup(BUTTON);

//     // Step 1
//     gpio_enable_event_detection(BUTTON, GPIO_DETECT_FALLING_EDGE);

//     // int drawn = -1;
//     // int prev_gCount = gCount;

//     while (true) {
//         // drawn = gCount;
//         if(!rb_empty(rb)){
//             int val = 0;
//         // if(prev_gCount < gCount){
//             rb_dequeue(rb, &val);
//             redraw(val);
//             // prev_gCount = gCount;
//         }
//     }
//     gpio_disable_event_detection(BUTTON, GPIO_DETECT_FALLING_EDGE);
//     gpio_interrupts_disable();

//     interrupts_global_disable();



// }


// void main(void) {
//     while (true){
//         timer_delay(5);
//         char c = glove_read_char(); // TODO: check name
//         glove_reset(); // TODO: check name
//         printf("%c", c); // TODO: could uart output faster, but need initialization if so
//     }
// }


struct Cursor{ 
    int x;
};

void main(void) {
    // TODO: init flex, accelerometer
    printf("Begin reading");
    char prevChar = '0'; // a placeholder \neq ' '
    struct Cursor cursor;
    cursor.x = 0;
    int time = 0;

    while (true){
        timer_delay(5);

        printf("Time %d", time);
        time ++;

        char c = glove_read_char(); // TODO: check name
        // glove_reset(); // TODO: check name
        if (c == '\b'){
            if (cursor.x >= 1){
                printf("%c", '\b');
                printf("%c", ' ');
                printf("%c", '\b');
                cursor.x --;
            }
        }
        elif (c == ' '){
            if (prevChar != ' '){
                printf("%c", ' '); // TODO: could uart output faster, but need initialization if so
            }
        }
        else {
            printf("%c", c); // TODO: could uart output faster, but need initialization if so
        }
    }
}