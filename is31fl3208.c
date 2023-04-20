#include "is31fl3208.h"
#include <stdint.h>

static Is31flDevice *dev_ptr;

void is31fl_init(Is31flDevice *dev)
{
    uint8_t i_max = I_MAX;
    uint8_t update = 0;
    dev_ptr = dev;
    for(int i = 0x14; i < 0x26; i++)
    {
        dev_ptr->is31fl_write_byte(dev_ptr->address, i, &i_max);
        dev_ptr->is31fl_write_byte(dev_ptr->address, UPDATE_REGISTER, &update);
    }
}
void is31fl_hardware_enable(bool enable)
{
    dev_ptr->hardware_enable(enable);
}

void is31fl_software_enable(bool enable)
{
    if(enable)
    {
        uint8_t set = 1;
        dev_ptr->is31fl_write_byte(dev_ptr->address, SHUTDOWN_REGISTER, &set);
    }
    else
    {
        uint8_t set = 0;
        dev_ptr->is31fl_write_byte(dev_ptr->address, SHUTDOWN_REGISTER, &set);
    }
}
void is31fl_reset_registers()
{
    uint8_t bit_reset = 0;
    dev_ptr->is31fl_write_byte(dev_ptr->address, RESET_REGISTER, &bit_reset);
}

void is31fl_set_leds(Led leds, Color c, uint8_t brightenes)
{
    uint8_t bit_reset = 0;
    uint8_t i = 1;

    c.blue = c.blue * brightenes / 100;
    c.green = c.green * brightenes / 100;
    c.red = c.red * brightenes / 100;
    for(uint8_t temp = 1; temp < ALL_LEDS; temp = temp * 2)
    {
        if(temp & leds)
        {
            dev_ptr->is31fl_write_byte(dev_ptr->address, i, &c.green);
            dev_ptr->is31fl_write_byte(dev_ptr->address, UPDATE_REGISTER,
                                       &bit_reset);

            dev_ptr->is31fl_write_byte(dev_ptr->address, i + 1, &c.red);
            dev_ptr->is31fl_write_byte(dev_ptr->address, UPDATE_REGISTER,
                                       &bit_reset);

            dev_ptr->is31fl_write_byte(dev_ptr->address, i + 2, &c.blue);
            dev_ptr->is31fl_write_byte(dev_ptr->address, UPDATE_REGISTER,
                                       &bit_reset);
        }
        i += 3;
    }
}

void is31fl_set_output_frequency(uint8_t frequency)
{
    dev_ptr->is31fl_write_byte(dev_ptr->address, OUTPUT_FREQUENCY_REGISTER,
                               &frequency);
}
