#pragma once

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

#define SHUTDOWN_REGISTER 0x00
#define UPDATE_REGISTER 0x13
#define GLOBAL_CONTROL_REGISTER
#define OUTPUT_FREQUENCY_REGISTER 0x27
#define RESET_REGISTER 0x2F

#define PWM_REGISTER_0 0x01
#define PWM_REGISTER_1 0x02
#define PWM_REGISTER_2 0x03
#define PWM_REGISTER_3 0x04
#define PWM_REGISTER_4 0x05
#define PWM_REGISTER_5 0x06
#define PWM_REGISTER_6 0x07
#define PWM_REGISTER_7 0x08
#define PWM_REGISTER_8 0x09
#define PWM_REGISTER_9 0x0A
#define PWM_REGISTER_10 0x0B
#define PWM_REGISTER_11 0x0C
#define PWM_REGISTER_12 0x0D
#define PWM_REGISTER_13 0x0E
#define PWM_REGISTER_14 0x0F
#define PWM_REGISTER_15 0x10
#define PWM_REGISTER_16 0x11
#define PWM_REGISTER_17 0x12

#define LED_CONTROL_REGISTER_0 0x14
#define LED_CONTROL_REGISTER_1 0x15
#define LED_CONTROL_REGISTER_2 0x16
#define LED_CONTROL_REGISTER_3 0x17
#define LED_CONTROL_REGISTER_4 0x18
#define LED_CONTROL_REGISTER_5 0x19
#define LED_CONTROL_REGISTER_6 0x1A
#define LED_CONTROL_REGISTER_7 0x18
#define LED_CONTROL_REGISTER_8 0x1C
#define LED_CONTROL_REGISTER_9 0x1D
#define LED_CONTROL_REGISTER_10 0x1E
#define LED_CONTROL_REGISTER_11 0x1F
#define LED_CONTROL_REGISTER_12 0x20
#define LED_CONTROL_REGISTER_13 0x21
#define LED_CONTROL_REGISTER_14 0x22
#define LED_CONTROL_REGISTER_15 0x23
#define LED_CONTROL_REGISTER_16 0x24
#define LED_CONTROL_REGISTER_17 0x25

#define OUTPUT_FREQUENCY_23K 0
#define OUTPUT_FREQUENCY_3_45K 1

#define REGISTER_OFFSET 0x13
#define ALL_LEDS 0x21

    typedef enum
    {
        I_MAX = 0x10,
        I_11_12 = 0x11,
        I_9_12 = 0x12,
        I_7_12 = 0x13,
        i_0 = 0x0
    } LedCurrent;

    typedef enum
    {
        LED0 = 0x1,
        LED1 = 0x2,
        LED2 = 0x4,
        LED3 = 0x8,
        LED4 = 0x10,
        LED5 = 0x20
    } Led;

    typedef struct
    {
        uint8_t red;
        uint8_t green;
        uint8_t blue;
    } Color;

    typedef struct
    {
        void (*is31fl_write_byte)(uint8_t address, uint8_t reg, uint8_t *data);
        void (*hardware_enable)(bool enable);
        uint8_t address;
    } Is31flDevice;

    void is31fl_init(Is31flDevice *dev);
    void is31fl_hardware_enable(bool enable);
    void is31fl_software_enable(bool enable);
    void is31fl_reset_registers();
    void is31fl_set_leds(Led leds, Color c, uint8_t brightenes);
    void is31fl_set_output_frequency(uint8_t frequency);

#ifdef __cplusplus
}
#endif
