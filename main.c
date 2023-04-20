#include "is31fl3208.h"
#include "led_ui.h"
#include "led_ui_charging.h"
#include "led_ui_receiving.h"
#include "led_ui_sending.h"
#include <driver/gpio.h>
#include <driver/i2c.h>
#include <esp_log.h>
#include <esp_timer.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <stdio.h>

#define INPUT_PIN_1 32
#define INPUT_PIN_2 33

static void IRAM_ATTR gpio_interrupt_handler(void *args)
{
    static bool state = true;
    if(state)
    {
        led_ui_task_start(LED_UI_CHARGING);
    }
    else
    {
        led_ui_task_stop(LED_UI_CHARGING);
    }
    state = !state;
}

static void IRAM_ATTR gpio_interrupt_handler_2(void *args)
{
    static bool state = true;
    if(state)
    {
        led_ui_task_start(LED_UI_SENDING);
    }
    else
    {
        led_ui_task_stop(LED_UI_SENDING);
    }
    state = !state;
}

void setup()
{
    i2c_config_t conf = {.mode = I2C_MODE_MASTER,
                         .sda_io_num = 21,
                         .sda_pullup_en = GPIO_PULLUP_DISABLE,
                         .scl_io_num = 22,
                         .scl_pullup_en = GPIO_PULLUP_DISABLE,
                         .master.clk_speed = 400000};

    i2c_param_config(I2C_NUM_0, &conf);
    i2c_driver_install(I2C_NUM_0, I2C_MODE_MASTER, 1, 1, 0);

    gpio_set_direction(GPIO_NUM_2, GPIO_MODE_OUTPUT);

    const esp_timer_create_args_t my_timer_args = {.callback = &led_ui_task_run,
                                                   .name = "My Timer"};
    esp_timer_handle_t timer_handler;
    ESP_ERROR_CHECK(esp_timer_create(&my_timer_args, &timer_handler));
    ESP_ERROR_CHECK(esp_timer_start_periodic(timer_handler, TIMER_PERIOD));

    // 32 and 33 pins for input

    gpio_set_direction(INPUT_PIN_1, GPIO_MODE_INPUT);
    gpio_pulldown_en(INPUT_PIN_1);
    gpio_pullup_dis(INPUT_PIN_1);
    gpio_set_intr_type(INPUT_PIN_1, GPIO_INTR_POSEDGE);
    gpio_install_isr_service(0);
    gpio_isr_handler_add(INPUT_PIN_1, gpio_interrupt_handler,
                         (void *)INPUT_PIN_1);

    gpio_set_direction(INPUT_PIN_2, GPIO_MODE_INPUT);
    gpio_pulldown_en(INPUT_PIN_2);
    gpio_pullup_dis(INPUT_PIN_2);
    gpio_set_intr_type(INPUT_PIN_2, GPIO_INTR_POSEDGE);
    gpio_isr_handler_add(INPUT_PIN_2, gpio_interrupt_handler_2,
                         (void *)INPUT_PIN_2);
}

void enable(bool en)
{
    if(en)
    {
        gpio_set_level(GPIO_NUM_2, 0);
    }
    else
    {
        gpio_set_level(GPIO_NUM_2, 1);
    }
}

void i2c_fn(uint8_t address, uint8_t reg, uint8_t *data)
{
    uint8_t arr[2];
    arr[0] = reg;
    arr[1] = *data;
    i2c_master_write_to_device(I2C_NUM_0, address, arr, 2, 100);
}

void app_main(void)
{
    setup();
    Is31flDevice dev = {.hardware_enable = &enable,
                        .is31fl_write_byte = &i2c_fn,
                        .address = 0x6C};

    is31fl_init(&dev);

    led_ui_task_register(LED_UI_SENDING, &led_ui_sending);
    led_ui_task_register(LED_UI_RECEIVING, &led_ui_receiving);
    led_ui_task_register(LED_UI_CHARGING, &led_ui_charging);
    led_ui_task_start(LED_UI_RECEIVING);
    while(1)
    {
        vTaskDelay(250 / portTICK_PERIOD_MS);
    }
}
