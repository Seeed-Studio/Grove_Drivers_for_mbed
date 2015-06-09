


#ifndef __GROVE_GYROSCOPE_CLASS_H__
#define __GROVE_GYROSCOPE_CLASS_H__

#include "grove_gyroscope.h"

//GROVE_NAME        "Grove_Gyroscope"
//IF_TYPE           I2C
//IMAGE_URL         http://www.seeedstudio.com/wiki/File:Gbgr.jpg

class GroveGyroscope
{
public:
    GroveGyroscope(int pinsda, int pinscl);
    bool write_setup(void);
    bool read_gyroscope(float *gx, float *gy, float *gz);
	bool write_zerocalibrate(void);
    
private:
    I2C_T *i2c;
};

#endif
