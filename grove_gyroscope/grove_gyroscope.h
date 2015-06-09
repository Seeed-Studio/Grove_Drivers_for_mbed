


#ifndef __GROVE_GYROSCOPE_LIGHT_H__
#define __GROVE_GYROSCOPE_LIGHT_H__

#include "suli2.h"

#define GYRO_ADDRESS (0x68<<1)

// ITG3200 Register Defines
#define ITG3200_WHO		0x00
#define	ITG3200_SMPL	0x15
#define ITG3200_DLPF	0x16
#define ITG3200_INT_C	0x17
#define ITG3200_INT_S	0x1A
#define	ITG3200_TMP_H	0x1B
#define	ITG3200_TMP_L	0x1C
#define	ITG3200_GX_H	0x1D
#define	ITG3200_GX_L	0x1E
#define	ITG3200_GY_H	0x1F
#define	ITG3200_GY_L	0x20
#define ITG3200_GZ_H	0x21
#define ITG3200_GZ_L	0x22
#define ITG3200_PWR_M	0x3E


void grove_gyroscope_init(I2C_T *i2c, int pinsda, int pinscl);
bool grove_gyro_write_setup(I2C_T *i2c);
bool grove_gyro_getangularvelocity(I2C_T *i2c, float *ax,float *ay,float *az);
bool grove_gyro_zerocalibrate(I2C_T *i2c);

#endif
