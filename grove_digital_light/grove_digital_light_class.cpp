

#include "grove_digital_light_class.h"

GroveDigitalLight::GroveDigitalLight(int pinsda, int pinscl)
{
    this->i2c = (I2C_T *)malloc(sizeof(I2C_T));
    grove_digital_light_init(this->i2c, pinsda, pinscl);
}

bool GroveDigitalLight::write_setup(void)
{
    return grove_digital_light_write_setup(this->i2c);
}

bool GroveDigitalLight::read_lux(uint32_t *lux)
{
    return grove_digital_light_readvisiblelux(this->i2c, lux);
}




