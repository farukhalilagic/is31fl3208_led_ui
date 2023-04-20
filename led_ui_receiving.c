#include "led_ui_receiving.h"
#include "is31fl3208.h"

void led_ui_receiving()
{
    Color c = {.red = 75, .green = 0, .blue = 130};
    is31fl_set_leds(LED1 | LED0 | LED2 | LED3 | LED4 | LED5, c, 0);
    static uint8_t first = LED0;
    static uint8_t second = LED5;
    static uint8_t first_off = LED2;
    static uint8_t second_off = LED3;
    led_ui_set_leds_mode(c, first | second, ON, 100);
    led_ui_set_leds_mode(c, first_off | second_off, OFF, 0);
    first = first << 1;
    second = second >> 1;
    first_off = first_off << 1;
    second_off = second_off >> 1;
    if(first > LED2)
    {
        first = LED0;
    }
    if(second < LED3)
    {
        second = LED5;
    }
    if(first_off > LED2)
    {
        first_off = LED0;
    }
    if(second_off < LED3)
    {
        second_off = LED5;
    }
}
