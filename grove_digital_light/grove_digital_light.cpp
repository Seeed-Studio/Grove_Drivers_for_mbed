

#include "suli2.h"
#include "grove_digital_light.h"



//local functions
static void grove_digital_light_getlux(I2C_T *i2c);
static unsigned long grove_digital_light_calculatelux(unsigned int iGain, unsigned int tInt, int iType);

//local variables
static unsigned char cmdbuf[2];
static uint16_t ch0, ch1;
static unsigned long chScale;
static unsigned long channel1;
static unsigned long channel0;
static unsigned long  ratio1;
static unsigned int b;
static unsigned int m;
static unsigned long temp;
static unsigned long lux;



void grove_digital_light_init(I2C_T *i2c, int pinsda, int pinscl)
{
    suli_i2c_init(i2c, pinsda, pinscl);
}

bool grove_digital_light_write_setup(I2C_T *i2c)
{
	cmdbuf[0] = TSL2561_Control;
	cmdbuf[1] = 0x03;
	suli_i2c_write(i2c, TSL2561_Address, cmdbuf, 2);  // POWER UP
	cmdbuf[0] = TSL2561_Timing;
	cmdbuf[1] = 0x00;
	suli_i2c_write(i2c, TSL2561_Address, cmdbuf, 2);  //No High Gain (1x), integration time of 13ms
	cmdbuf[0] = TSL2561_Interrupt;
	cmdbuf[1] = 0x00;
	suli_i2c_write(i2c, TSL2561_Address, cmdbuf, 2);  
	cmdbuf[0] = TSL2561_Control;
	cmdbuf[1] = 0x00;
	suli_i2c_write(i2c, TSL2561_Address, cmdbuf, 2);  // POWER Down
	
    return true;
}

static void grove_digital_light_getlux(I2C_T *i2c)
{
	uint8_t CH0_LOW = 0, CH0_HIGH = 0, CH1_LOW = 0, CH1_HIGH = 0;

	cmdbuf[0] = TSL2561_Channal0L;
	suli_i2c_write(i2c, TSL2561_Address, cmdbuf, 1);
	suli_i2c_read(i2c, TSL2561_Address, &CH0_LOW, 1);
	cmdbuf[0] = TSL2561_Channal0H;
	suli_i2c_write(i2c, TSL2561_Address, cmdbuf, 1);
	suli_i2c_read(i2c, TSL2561_Address, &CH0_HIGH, 1);
	cmdbuf[0] = TSL2561_Channal1L;
	suli_i2c_write(i2c, TSL2561_Address, cmdbuf, 1);
	suli_i2c_read(i2c, TSL2561_Address, &CH1_LOW, 1);
	cmdbuf[0] = TSL2561_Channal1H;
	suli_i2c_write(i2c, TSL2561_Address, cmdbuf, 1);
	suli_i2c_read(i2c, TSL2561_Address, &CH1_HIGH, 1);

	ch0 = (CH0_HIGH<<8) | CH0_LOW;
	ch1 = (CH1_HIGH<<8) | CH1_LOW;
}

static unsigned long grove_digital_light_calculatelux(unsigned int iGain, unsigned int tInt, int iType)
{
	switch (tInt)
	{
		case 0:  // 13.7 msec
			chScale = CHSCALE_TINT0;
			break;
		case 1: // 101 msec
			chScale = CHSCALE_TINT1;
			break;
		default: // assume no scaling
			chScale = (1 << CH_SCALE);
			break;
	}
	if (!iGain)  chScale = chScale << 4; // scale 1X to 16X
	// scale the channel values
	channel0 = (ch0 * chScale) >> CH_SCALE;
	channel1 = (ch1 * chScale) >> CH_SCALE;

	ratio1 = 0;
	if (channel0!= 0) ratio1 = (channel1 << (RATIO_SCALE+1))/channel0;
	// round the ratio value
	unsigned long ratio = (ratio1 + 1) >> 1;

	switch (iType)
	{
		case 0: // T package
			if ((ratio >= 0) && (ratio <= K1T))
			{b=B1T; m=M1T;}
			else if (ratio <= K2T)
			{b=B2T; m=M2T;}
			else if (ratio <= K3T)
			{b=B3T; m=M3T;}
			else if (ratio <= K4T)
			{b=B4T; m=M4T;}
			else if (ratio <= K5T)
			{b=B5T; m=M5T;}
			else if (ratio <= K6T)
			{b=B6T; m=M6T;}
			else if (ratio <= K7T)
			{b=B7T; m=M7T;}
			else if (ratio > K8T)
			{b=B8T; m=M8T;}
			break;
		case 1:// CS package
			if ((ratio >= 0) && (ratio <= K1C))
			{b=B1C; m=M1C;}
			else if (ratio <= K2C)
			{b=B2C; m=M2C;}
			else if (ratio <= K3C)
			{b=B3C; m=M3C;}
			else if (ratio <= K4C)
			{b=B4C; m=M4C;}
			else if (ratio <= K5C)
			{b=B5C; m=M5C;}
			else if (ratio <= K6C)
			{b=B6C; m=M6C;}
			else if (ratio <= K7C)
			{b=B7C; m=M7C;}
	}
	temp=((channel0*b)-(channel1*m));
	if(temp<0) temp=0;
	temp+=(1<<(LUX_SCALE-1));
	// strip off fractional portion
	lux=temp>>LUX_SCALE;
	return (lux);
}

bool grove_digital_light_readvisiblelux(I2C_T *i2c, uint32_t *lux)
{
	cmdbuf[0] = TSL2561_Control;
	cmdbuf[1] = 0x03;
	suli_i2c_write(i2c, TSL2561_Address, cmdbuf, 2);  // POWER UP
	suli_delay_ms(14);
	grove_digital_light_getlux(i2c);

	cmdbuf[0] = TSL2561_Control;
	cmdbuf[1] = 0x00;
	suli_i2c_write(i2c, TSL2561_Address, cmdbuf, 2);  // POWER Down
	if(ch0/ch1 < 2 && ch0 > 4900)
	{
		return -1;  //ch0 out of range, but ch1 not. the lux is not valid in this situation.
	}
	*lux = grove_digital_light_calculatelux(0, 0, 0);  //T package, no gain, 13ms
	return true;
}

