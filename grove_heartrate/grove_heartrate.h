


#ifndef __GROVE_HEARTRATE_H__
#define __GROVE_HEARTRATE_H__

#include "suli2.h"

#define HEARTRATE_ADDRESS (0xA0)

void grove_heartrate_init(I2C_T *i2c, int pinsda, int pinscl);
bool grove_heartrate_write_setup(I2C_T *i2c);
bool grove_heartrate_getheartrate(I2C_T *i2c, uint8_t *heartrate);

#endif
