

#include "grove_moisture_class.h"

GroveMoisture::GroveMoisture(int pin)
{
    this->analog = (ANALOG_T *)malloc(sizeof(ANALOG_T));
    grove_moisture_init(this->analog, pin);
}

bool GroveMoisture::write_setup(void)
{
    return grove_moisture_write_setup(this->analog);
}

bool GroveMoisture::read_moisture(uint16_t *moisture)
{
    return grove_moisture_readmoisture(analog, moisture);
}
