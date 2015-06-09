


#ifndef __GROVE_COMPASS_H__
#define __GROVE_COMPASS_H__

#include "suli2.h"

#define HMC5883L_ADDRESS (0x1E<<1)

#define CONFIGURATION_REGISTERA 0x00
#define CONFIGURATION_REGISTERB 0x01
#define MODE_REGISTER 0x02
#define DATA_REGISTER_BEGIN 0x03

#define MEASUREMENT_CONTINUOUS 0x00
#define MEASUREMENT_SINGLE_SHOT 0x01
#define MEASUREMENT_IDLE 0x03

#define PI ((float)3.1415926)

void grove_compass_init(I2C_T *i2c, int pinsda, int pinscl);
bool grove_compass_write_setup(I2C_T *i2c);
bool grove_compass_getxyz_scaled(I2C_T *i2c, float *ax, float *ay, float *az);
bool grove_compass_getheading(I2C_T *i2c, float *heading);

#endif
