

#include "grove_heartrate_class.h"

GroveHeartrate::GroveHeartrate(int pinsda, int pinscl)
{
    this->i2c = (I2C_T *)malloc(sizeof(I2C_T));
    grove_heartrate_init(this->i2c, pinsda, pinscl);
}

bool GroveHeartrate::write_setup(void)
{
    return grove_heartrate_write_setup(this->i2c);
}

bool GroveHeartrate::read_heartrate(uint8_t *lux)
{
    return grove_heartrate_getheartrate(this->i2c, lux);
}
