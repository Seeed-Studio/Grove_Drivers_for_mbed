

#include "grove_accelerometer_class.h"

GroveAccelerometer::GroveAccelerometer(int pinsda, int pinscl)
{
    this->i2c = (I2C_T *)malloc(sizeof(I2C_T));
    grove_accelerometer_init(this->i2c, pinsda, pinscl);
}

bool GroveAccelerometer::write_setup(void)
{
    return grove_accelerometer_write_setup(this->i2c);
}

bool GroveAccelerometer::read_accelerometer(float *ax, float *ay, float *az)
{
    return grove_accelerometer_getacceleration(this->i2c, ax, ay, az);
}




