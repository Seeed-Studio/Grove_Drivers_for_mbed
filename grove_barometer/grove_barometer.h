


#ifndef __GROVE_BAROMETER_H__
#define __GROVE_BAROMETER_H__

#include "suli2.h"

#define BMP085_ADDRESS (0x77<<1)

void grove_barometer_init(I2C_T *i2c, int pinsda, int pinscl);
bool grove_barometer_write_setup(I2C_T *i2c);
bool grove_barometer_gettemperature(I2C_T *i2c, float *temperature);
bool grove_barometer_getpressure(I2C_T *i2c, long *pressure);
bool grove_barometer_calcaltitude(I2C_T *i2c, float *altitude);

#endif
