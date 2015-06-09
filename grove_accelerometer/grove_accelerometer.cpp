

#include "suli2.h"
#include "grove_accelerometer.h"



//local functions
static void grove_accelerometer_setmode(I2C_T *i2c, uint8_t mode);
static void grove_accelerometer_setsamplerate(I2C_T *i2c, uint8_t rate);
static void grove_accelerometer_getxyz(I2C_T *i2c, int8_t *x, int8_t *y, int8_t *z);

//local variables
static unsigned char cmdbuf[2];


void grove_accelerometer_init(I2C_T *i2c, int pinsda, int pinscl)
{
    suli_i2c_init(i2c, pinsda, pinscl);
}

bool grove_accelerometer_write_setup(I2C_T *i2c)
{
	grove_accelerometer_setmode(i2c, MMA7660_STAND_BY);
    grove_accelerometer_setsamplerate(i2c, AUTO_SLEEP_32);
    grove_accelerometer_setmode(i2c, MMA7660_ACTIVE);
	
    return true;
}

static void grove_accelerometer_setmode(I2C_T *i2c, uint8_t mode)
{
    //write(MMA7660_MODE,mode);	
	cmdbuf[0] = MMA7660_MODE;
	cmdbuf[1] = mode;
	suli_i2c_write(i2c, MMA7660_ADDR, cmdbuf, 2);
	
}
static void grove_accelerometer_setsamplerate(I2C_T *i2c, uint8_t rate)
{
    //write(MMA7660_SR,rate);
	cmdbuf[0] = MMA7660_SR;
	cmdbuf[1] = rate;
	suli_i2c_write(i2c, MMA7660_ADDR, cmdbuf, 2);
}

/*Function: Get the contents of the registers in the MMA7660*/
/*          so as to calculate the acceleration.            */
static void grove_accelerometer_getxyz(I2C_T *i2c, int8_t *x, int8_t *y, int8_t *z)
{
    unsigned char val[3];
    val[0] = val[1] = val[2] = 64;

	suli_i2c_read(i2c, MMA7660_ADDR, val, 3);
	
    *x = ((char)(val[0]<<2))/4;
    *y = ((char)(val[1]<<2))/4;
    *z = ((char)(val[2]<<2))/4;
}

bool grove_accelerometer_getacceleration(I2C_T *i2c, float *ax, float *ay, float *az)
{
    int8_t x,y,z;
    grove_accelerometer_getxyz(i2c, &x,&y,&z);
    *ax = x/21.00;
    *ay = y/21.00;
    *az = z/21.00;
	
	return true;
}



