

#include "grove_gyroscope_class.h"

GroveGyroscope::GroveGyroscope(int pinsda, int pinscl)
{
    this->i2c = (I2C_T *)malloc(sizeof(I2C_T));
    grove_gyroscope_init(this->i2c, pinsda, pinscl);
}

bool GroveGyroscope::write_setup(void)
{
    return grove_gyro_write_setup(this->i2c);
}

bool GroveGyroscope::read_gyroscope(float *gx, float *gy, float *gz)
{
    return grove_gyro_getangularvelocity(this->i2c, gx, gy, gz);
}

bool GroveGyroscope::write_zerocalibrate(void)
{
    return grove_gyro_zerocalibrate(this->i2c);
}
