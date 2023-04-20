#include "led_ui.h"
#include "is31fl3208.h"
#include <esp_log.h>
#include <stdbool.h>

static Task led_ui_tasks[LED_UI_LAST];
static uint8_t count = 0;
static uint8_t tick = 0;

void led_ui_task_register(TaskPriority priority, void (*func_ptr)(void))
{
    Task temp = {.f_ptr = func_ptr, .state = false};
    led_ui_tasks[priority] = temp;
    is31fl_hardware_enable(true);
    is31fl_software_enable(true);
}

void led_ui_task_start(TaskPriority priority)
{
    led_ui_tasks[priority].state = true;
}

void led_ui_task_stop(TaskPriority priority)
{
    led_ui_tasks[priority].state = false;
}

void led_ui_task_run()
{
    for(int i = 0; i < LED_UI_LAST; i++)
    {
        if(led_ui_tasks[i].state == true)
        {
            led_ui_tasks[i].f_ptr();
            break;
        }
    }
    tick++;
    if(tick > 3)
    {
        tick = 0;
    }
}

void led_ui_set_leds_mode(Color color, Led leds, BlinkMode mode,
                          uint8_t brightenes)
{
    static bool on = false;
    if(count > 3)
    {
        count = 0;
    }
    switch(mode)
    {
    case OFF:
        on = false;
        break;
    case ON:
        on = true;
        break;
    case BLINK:
        if(count % 2)
        {
            on = !on;
        }
        break;
    case BLINK_FAST:
        on = !on;
        break;
    case BLINK_SLOW:
        if(count == 0)
        {
            on = !on;
        }
        break;
    default:
        break;
    }

    if(on)
    {
        is31fl_set_leds(leds, color, brightenes);
    }
    else
    {
        is31fl_set_leds(leds, color, 0);
    }
    count++;
}

uint8_t led_ui_get_tick()
{
    return tick;
}
