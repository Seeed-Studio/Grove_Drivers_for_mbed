

#include "grove_comp_hmc5883l.h"

GroveCompass::GroveCompass(int pinsda, int pinscl)
{
    this->i2c = (I2C_T *)malloc(sizeof(I2C_T));
    suli_i2c_init(i2c, pinsda, pinscl);
}

bool GroveCompass::GroveCompass::write_setup(void)
{
    uint8_t regValue = 0x00;
	
	//setScale(this->i2c, (float)1.3); // Set the scale of the compass.
	regValue = 0x01;
	m_Scale = 0.92;
	// Setting is in the top 3 bits of the register.
	regValue = regValue << 5;
	//write(CONFIGURATION_REGISTERB, regValue);
	cmdbuf[0] = CONFIGURATION_REGISTERB;
	cmdbuf[1] = regValue;
	suli_i2c_write(this->i2c, HMC5883L_ADDRESS, cmdbuf, 2);
	setMeasurementMode(this->i2c, MEASUREMENT_CONTINUOUS); // Set the measurement mode to Continuous
	
    return true;
}

void GroveCompass::setMeasurementMode(I2C_T *i2c, uint8_t mode)
{
	//write(MODE_REGISTER, mode);
	cmdbuf[0] = MODE_REGISTER;
	cmdbuf[1] = mode;
	suli_i2c_write(i2c, HMC5883L_ADDRESS, cmdbuf, 2);
}

void GroveCompass::grove_compass_getxyz_raw(I2C_T *i2c, int16_t *x, int16_t *y, int16_t *z)
{
	cmdbuf[0] = DATA_REGISTER_BEGIN;
	suli_i2c_write(i2c, HMC5883L_ADDRESS, &cmdbuf[0], 1);
	suli_i2c_read(i2c, HMC5883L_ADDRESS, databuf, 6);
	*x = (databuf[0] << 8) | databuf[1];
	*y = (databuf[2] << 8) | databuf[3];
	*z = (databuf[4] << 8) | databuf[5];
}

bool GroveCompass::grove_compass_getxyz_scaled(I2C_T *i2c, float *cx, float *cy, float *cz)
{
    int16_t x,y,z;
	
    grove_compass_getxyz_raw(i2c, &x,&y,&z);
	*cx = (float)x * m_Scale;
	*cy = (float)y * m_Scale;
	*cz = (float)z * m_Scale;

	return true;
}

bool GroveCompass::read_compass_heading(float *heading)
{
    float cx, cy, cz;
	
	grove_compass_getxyz_scaled(this->i2c, &cx, &cy, &cz);
	
	float head = atan2(cy, cx) - 0.0457;
	
	// Correct for when signs are reversed.
	if(head < 0)
	head += 2*PI;

	// Check for wrap due to addition of declination.
	if(head > 2*PI)
	head -= 2*PI;

	// Convert radians to degrees for readability.
	*heading = head * 180 / PI;
	
	return true;
}

