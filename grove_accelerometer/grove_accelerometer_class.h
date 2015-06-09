


#ifndef __GROVE_ACCELERMETER_CLASS_H__
#define __GROVE_ACCELERMETER_CLASS_H__

#include "grove_accelerometer.h"

//GROVE_NAME        "Grove_Accelerometer"
//IF_TYPE           I2C
//IMAGE_URL         http://www.seeedstudio.com/wiki/images/b/bb/3_aix_acc.jpg

class GroveAccelerometer
{
public:
    GroveAccelerometer(int pinsda, int pinscl);
    bool write_setup(void);
    bool read_accelerometer(float *ax, float *ay, float *az);
    
private:
    I2C_T *i2c;
};

#endif
