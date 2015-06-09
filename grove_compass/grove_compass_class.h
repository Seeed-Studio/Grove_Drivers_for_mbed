


#ifndef __GROVE_COMPASS_CLASS_H__
#define __GROVE_COMPASS_CLASS_H__

#include "grove_compass.h"

//GROVE_NAME        "Grove_Compass"
//IF_TYPE           I2C
//IMAGE_URL         http://www.seeedstudio.com/wiki/File:3_axis_compass.jpg

class GroveCompass
{
public:
    GroveCompass(int pinsda, int pinscl);
	bool write_setup(void);
    bool read_compass_xyz(float *cx, float *cy, float *cz);
    bool read_compass_heading(float *heading);

private:
    I2C_T *i2c;
};

#endif
