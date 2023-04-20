#include "led_ui_charging.h"
#include "is31fl3208.h"

void led_ui_charging()
{
    Color c = {.red = 0, .green = 102, .blue = 102};
    is31fl_set_leds(LED1 | LED0 | LED2 | LED3 | LED4 | LED5, c, 0);
    static uint8_t led = LED0;
    static uint8_t led_off = LED5;

    led_ui_set_leds_mode(c, led, ON, 100);
    led_ui_set_leds_mode(c, led_off, OFF, 0);
    led = led << 1;
    led_off = led_off << 1;

    if(led > LED5)
    {
        led = LED0;
    }

    if(led_off > LED5)
    {
        led_off = LED0;
    }
}
