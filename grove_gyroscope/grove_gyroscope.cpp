

#include "suli2.h"
#include "grove_gyroscope.h"



//local functions
static char _read_char(I2C_T *i2c, unsigned char addr);
static double grove_gyro_gettemperature(I2C_T *i2c);
static void grove_gyro_getxyz(I2C_T *i2c, int16_t *x,int16_t *y,int16_t *z);

//local variables
static unsigned char cmdbuf[2];
static unsigned char databuf[2];
static int16_t x_offset;
static int16_t y_offset;
static int16_t z_offset;

// Read 1 byte from I2C
static char _read_char(I2C_T *i2c, unsigned char addr)
{
	suli_i2c_write(i2c, GYRO_ADDRESS, &addr, 1);
	suli_i2c_read(i2c, GYRO_ADDRESS, databuf, 1);
	return databuf[0];
}

void grove_gyroscope_init(I2C_T *i2c, int pinsda, int pinscl)
{
    suli_i2c_init(i2c, pinsda, pinscl);
}

bool grove_gyro_write_setup(I2C_T *i2c)
{
	cmdbuf[0] = ITG3200_PWR_M;
	cmdbuf[1] = 0x80;
	suli_i2c_write(i2c, GYRO_ADDRESS, cmdbuf, 2);//send a reset to the device
	cmdbuf[0] = ITG3200_SMPL;
	cmdbuf[1] = 0x00;
	suli_i2c_write(i2c, GYRO_ADDRESS, cmdbuf, 2);//sample rate divider
	cmdbuf[0] = ITG3200_DLPF;
	cmdbuf[1] = 0x18;
	suli_i2c_write(i2c, GYRO_ADDRESS, cmdbuf, 2);//+/-2000 degrees/s (default value)
	
    return true;
}

/*Function: Get the temperature from ITG3200 that with a on-chip*/
/*           temperature sensor.                                */
static double grove_gyro_gettemperature(I2C_T *i2c)
{
	int temp;
	double temperature;
	//temp = read(ITG3200_TMP_H, ITG3200_TMP_L);
	temp = (_read_char(i2c, ITG3200_TMP_H) << 8) + _read_char(i2c, ITG3200_TMP_L);
	temperature = 35+ ((double) (temp + 13200)) / 280;
	return(temperature);
}

/*Function: Get the contents of the registers in the ITG3200*/
/*          so as to calculate the angular velocity.        */
static void grove_gyro_getxyz(I2C_T *i2c, int16_t *x,int16_t *y,int16_t *z)
{
	*x  = (_read_char(i2c, ITG3200_GX_H) << 8) + _read_char(i2c, ITG3200_GX_L) + x_offset;
	*y = (_read_char(i2c, ITG3200_GY_H) << 8) + _read_char(i2c, ITG3200_GY_L) + y_offset;
	*z = (_read_char(i2c, ITG3200_GZ_H) << 8) + _read_char(i2c, ITG3200_GZ_L) + z_offset;
}

/*Function: Get the angular velocity and its unit is degree per second.*/
bool grove_gyro_getangularvelocity(I2C_T *i2c, float *ax,float *ay,float *az)
{
	int16_t x,y,z;
	grove_gyro_getxyz(i2c, &x,&y,&z);
	*ax = x/14.375;
	*ay = y/14.375;
	*az = z/14.375;
	
	return true;
}

bool grove_gyro_zerocalibrate(I2C_T *i2c) 
{
  int16_t x_offset_temp;
  int16_t y_offset_temp;
  int16_t z_offset_temp;
  int16_t x,y,z;
  x_offset = 0;
  y_offset = 0;
  z_offset = 0;
  
  for (int i = 0;i < 200;i++){
    suli_delay_ms(10);
    grove_gyro_getxyz(i2c, &x,&y,&z);
    x_offset_temp += x;
    y_offset_temp += y;
    z_offset_temp += z;
  }

  x_offset = abs(x_offset_temp)/200;
  y_offset = abs(y_offset_temp)/200;
  z_offset = abs(z_offset_temp)/200;
  if(x_offset_temp > 0)x_offset = -x_offset;
  if(y_offset_temp > 0)y_offset = -y_offset;
  if(z_offset_temp > 0)z_offset = -z_offset;
  
  return true;
}
