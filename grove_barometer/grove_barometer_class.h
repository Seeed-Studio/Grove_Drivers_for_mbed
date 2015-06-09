


#ifndef __GROVE_BAROMETER_CLASS_H__
#define __GROVE_BAROMETER_CLASS_H__

#include "grove_barometer.h"

//GROVE_NAME        "Grove_Barometer"
//IF_TYPE           I2C
//IMAGE_URL         http://www.seeedstudio.com/wiki/File:Grove-Barometer.jpg

class GroveBarometer
{
public:
    GroveBarometer(int pinsda, int pinscl);
    bool write_setup(void);
    bool read_temperature(float *temperature);
	bool read_pressure(long *pressure);
	bool read_altitude(float *altitude);

private:
    I2C_T *i2c;
};

#endif
