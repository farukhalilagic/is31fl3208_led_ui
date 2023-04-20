#include "led_ui_sending.h"
#include "is31fl3208.h"
#include "led_ui.h"

void led_ui_sending()
{
    Color c = {.red = 128, .green = 128, .blue = 0};
    static uint8_t first_led = LED2;
    static uint8_t second_led = LED3;
    static uint8_t first_led_off = LED1;
    static uint8_t second_led_off = LED5;

    is31fl_set_leds(LED1 | LED0 | LED2 | LED3 | LED4 | LED5, c, 0);
    led_ui_set_leds_mode(c, first_led | second_led, ON, 100);
    led_ui_set_leds_mode(c, first_led_off | second_led_off, OFF, 0);
        first_led = first_led >> 1;
        second_led = second_led << 1;
        first_led_off = first_led_off >> 1;
        second_led_off = second_led_off << 1;
    if(first_led < 1)
    {
        first_led = LED2;
    }
    if(second_led > LED5)
    {
        second_led = LED3;
    }
    if(first_led_off < 1)
    {
        first_led_off = LED2;
    }
    if(second_led_off > LED5)
    {
        second_led_off = LED3;
    }
}
