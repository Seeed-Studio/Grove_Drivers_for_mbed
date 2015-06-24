


#ifndef __GROVE_COMPASS_CLASS_H__
#define __GROVE_COMPASS_CLASS_H__

#include "suli2.h"

//GROVE_NAME        "Grove_Compass"
//IF_TYPE           I2C
//IMAGE_URL         http://www.seeedstudio.com/wiki/File:3_axis_compass.jpg

#define HMC5883L_ADDRESS (0x1E<<1)

#define CONFIGURATION_REGISTERA 0x00
#define CONFIGURATION_REGISTERB 0x01
#define MODE_REGISTER 0x02
#define DATA_REGISTER_BEGIN 0x03

#define MEASUREMENT_CONTINUOUS 0x00
#define MEASUREMENT_SINGLE_SHOT 0x01
#define MEASUREMENT_IDLE 0x03

#define PI ((float)3.1415926)

class GroveCompass
{
public:
    GroveCompass(int pinsda, int pinscl);
	bool write_setup(void);
    bool read_compass_heading(float *heading);
	bool grove_compass_getxyz_scaled(I2C_T *i2c, float *cx, float *cy, float *cz);
private:
    I2C_T *i2c;
    float m_Scale;
    unsigned char cmdbuf[2];
    unsigned char databuf[6];
    
    void setMeasurementMode(I2C_T *i2c, uint8_t mode);
    void grove_compass_getxyz_raw(I2C_T *i2c, int16_t *x, int16_t *y, int16_t *z);
};

#endif
