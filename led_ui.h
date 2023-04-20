#pragma once
#include "is31fl3208.h"

#define TIMER_PERIOD 250000

typedef enum
{
    LED_UI_CHARGING = 0,
    LED_UI_SENDING,
    LED_UI_RECEIVING,
    LED_UI_LAST
} TaskPriority;

typedef enum
{
    OFF = 0,
    ON,
    BLINK,
    BLINK_FAST,
    BLINK_SLOW
} BlinkMode;

typedef struct
{
    bool state;
    void (*f_ptr)(void);
} Task;

void led_ui_task_register(TaskPriority priority, void (*f_prt)(void));
void led_ui_task_start(TaskPriority priority);
void led_ui_task_stop(TaskPriority priority);
void led_ui_task_run();
void led_ui_set_leds_mode(Color color, Led led, BlinkMode mode,
                          uint8_t brightenes);
uint8_t led_ui_get_tick();
