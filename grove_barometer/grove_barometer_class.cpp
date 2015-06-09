

#include "grove_barometer_class.h"

GroveBarometer::GroveBarometer(int pinsda, int pinscl)
{
    this->i2c = (I2C_T *)malloc(sizeof(I2C_T));
    grove_barometer_init(this->i2c, pinsda, pinscl);
}

bool GroveBarometer::write_setup(void)
{
    return grove_barometer_write_setup(this->i2c);
}

bool GroveBarometer::read_temperature(float *temperature)
{
    return grove_barometer_gettemperature(this->i2c, temperature);
}

bool GroveBarometer::read_pressure(long *pressure)
{
    return grove_barometer_getpressure(this->i2c, pressure);
}

bool GroveBarometer::read_altitude(float *altitude)
{
    return grove_barometer_calcaltitude(this->i2c, altitude);
}




