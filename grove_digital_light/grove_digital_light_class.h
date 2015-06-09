


#ifndef __GROVE_DIGITAL_LIGHT_CLASS_H__
#define __GROVE_DIGITAL_LIGHT_CLASS_H__

#include "grove_digital_light.h"

//GROVE_NAME        "Grove_DigitalLight"
//IF_TYPE           I2C
//IMAGE_URL         http://www.seeedstudio.com/wiki/File:Digital_Light_Sensor.jpg

class GroveDigitalLight
{
public:
    GroveDigitalLight(int pinsda, int pinscl);
    bool write_setup(void);
    bool read_lux(uint32_t *lux);

private:
    I2C_T *i2c;
};

#endif
