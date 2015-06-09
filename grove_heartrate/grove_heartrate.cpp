

#include "suli2.h"
#include "grove_heartrate.h"



//local functions

//local variables


void grove_heartrate_init(I2C_T *i2c, int pinsda, int pinscl)
{
    suli_i2c_init(i2c, pinsda, pinscl);
}

bool grove_heartrate_write_setup(I2C_T *i2c)
{
    return true;
}

bool grove_heartrate_getheartrate(I2C_T *i2c, uint8_t *heartrate)
{
	suli_i2c_read(i2c, HEARTRATE_ADDRESS, heartrate, 1);
}
