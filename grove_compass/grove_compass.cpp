

#include "suli2.h"
#include "grove_compass.h"

//local functions
static void grove_compass_getxyz_raw(I2C_T *i2c, int16_t *x, int16_t *y, int16_t *z);
static int setScale(I2C_T *i2c, float gauss);
static void setMeasurementMode(I2C_T *i2c, uint8_t mode);

//local variables
static float m_Scale;
static unsigned char cmdbuf[2];
static unsigned char databuf[6];

void grove_compass_init(I2C_T *i2c, int pinsda, int pinscl)
{
    suli_i2c_init(i2c, pinsda, pinscl);
}

bool grove_compass_write_setup(I2C_T *i2c)
{
	uint8_t regValue = 0x00;
	
	//setScale(i2c, (float)1.3); // Set the scale of the compass.
	regValue = 0x01;
	m_Scale = 0.92;
	// Setting is in the top 3 bits of the register.
	regValue = regValue << 5;
	//write(CONFIGURATION_REGISTERB, regValue);
	cmdbuf[0] = CONFIGURATION_REGISTERB;
	cmdbuf[1] = regValue;
	suli_i2c_write(i2c, HMC5883L_ADDRESS, cmdbuf, 2);
	setMeasurementMode(i2c, MEASUREMENT_CONTINUOUS); // Set the measurement mode to Continuous
	
    return true;
}

static void grove_compass_getxyz_raw(I2C_T *i2c, int16_t *x, int16_t *y, int16_t *z)
{
	cmdbuf[0] = DATA_REGISTER_BEGIN;
	suli_i2c_write(i2c, HMC5883L_ADDRESS, &cmdbuf[0], 1);
	suli_i2c_read(i2c, HMC5883L_ADDRESS, databuf, 6);
	*x = (databuf[0] << 8) | databuf[1];
	*y = (databuf[2] << 8) | databuf[3];
	*z = (databuf[4] << 8) | databuf[5];
}

bool grove_compass_getxyz_scaled(I2C_T *i2c, float *cx, float *cy, float *cz)
{
    int16_t x,y,z;
	
    grove_compass_getxyz_raw(i2c, &x,&y,&z);
	*cx = (float)x * m_Scale;
	*cy = (float)y * m_Scale;
	*cz = (float)z * m_Scale;

	return true;
}

bool grove_compass_getheading(I2C_T *i2c, float *heading)
{
	float cx, cy, cz;
	
	grove_compass_getxyz_scaled(i2c, &cx, &cy, &cz);
	
	float head = atan2(cy, cx) - 0.0457;
	
	// Correct for when signs are reversed.
	if(heading < 0)
	head += 2*PI;

	// Check for wrap due to addition of declination.
	if(head > 2*PI)
	head -= 2*PI;

	// Convert radians to degrees for readability.
	*heading = head * 180 / PI;
	
	return true;
}


static int setScale(I2C_T *i2c, float gauss)
{
	uint8_t regValue = 0x00;
	if(gauss == 0.88)
	{
		regValue = 0x00;
		m_Scale = 0.73;
	}
	else if(gauss == 1.3)
	{
		regValue = 0x01;
		m_Scale = 0.92;
	}
	else if(gauss == 1.9)
	{
		regValue = 0x02;
		m_Scale = 1.22;
	}
	else if(gauss == 2.5)
	{
		regValue = 0x03;
		m_Scale = 1.52;
	}
	else if(gauss == 4.0)
	{
		regValue = 0x04;
		m_Scale = 2.27;
	}
	else if(gauss == 4.7)
	{
		regValue = 0x05;
		m_Scale = 2.56;
	}
	else if(gauss == 5.6)
	{
		regValue = 0x06;
		m_Scale = 3.03;
	}
	else if(gauss == 8.1)
	{
		regValue = 0x07;
		m_Scale = 4.35;
	}
	else
		return -1;
	
	// Setting is in the top 3 bits of the register.
	regValue = regValue << 5;
	//write(CONFIGURATION_REGISTERB, regValue);
	cmdbuf[0] = CONFIGURATION_REGISTERB;
	cmdbuf[1] = regValue;
	suli_i2c_write(i2c, HMC5883L_ADDRESS, &cmdbuf[0], 2);
	
	return true;
}

static void setMeasurementMode(I2C_T *i2c, uint8_t mode)
{
	//write(MODE_REGISTER, mode);
	cmdbuf[0] = MODE_REGISTER;
	cmdbuf[1] = mode;
	suli_i2c_write(i2c, HMC5883L_ADDRESS, cmdbuf, 2);
}
