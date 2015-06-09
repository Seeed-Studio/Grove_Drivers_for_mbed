


#ifndef __GROVE_ACCELERMETER_H__
#define __GROVE_ACCELERMETER_H__

#include "suli2.h"

#define MMA7660_ADDR  (0x4c<<1)

#define MMA7660_X     0x00
#define MMA7660_Y     0x01
#define MMA7660_Z     0x02
#define MMA7660_TILT  0x03
#define MMA7660_SRST  0x04
#define MMA7660_SPCNT 0x05
#define MMA7660_INTSU 0x06
#define MMA7660_MODE  0x07
#define MMA7660_STAND_BY 0x00
#define MMA7660_ACTIVE   0x01   
#define MMA7660_SR    0x08      //sample rate register
#define AUTO_SLEEP_120  0X00//120 sample per second
#define AUTO_SLEEP_64   0X01
#define AUTO_SLEEP_32   0X02
#define AUTO_SLEEP_16   0X03
#define AUTO_SLEEP_8    0X04
#define AUTO_SLEEP_4    0X05
#define AUTO_SLEEP_2    0X06
#define AUTO_SLEEP_1    0X07
#define MMA7660_PDET  0x09
#define MMA7660_PD    0x0A

void grove_accelerometer_init(I2C_T *i2c, int pinsda, int pinscl);
bool grove_accelerometer_write_setup(I2C_T *i2c);
bool grove_accelerometer_getacceleration(I2C_T *i2c, float *ax,float *ay,float *az);

#endif
