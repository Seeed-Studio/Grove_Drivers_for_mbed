

#include "grove_compass_class.h"

GroveCompass::GroveCompass(int pinsda, int pinscl)
{
    this->i2c = (I2C_T *)malloc(sizeof(I2C_T));
    grove_compass_init(this->i2c, pinsda, pinscl);
}

bool GroveCompass::write_setup(void)
{
    return grove_compass_write_setup(this->i2c);
}

bool GroveCompass::read_compass_xyz(float *cx, float *cy, float *cz)
{
    return grove_compass_getxyz_scaled(this->i2c, cx, cy, cz);
}

bool GroveCompass::read_compass_heading(float *heading)
{
	return grove_compass_getheading(this->i2c, heading);
}

