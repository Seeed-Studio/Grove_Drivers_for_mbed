

#include "suli2.h"
#include "grove_barometer.h"



//local functions
static char _read_char(I2C_T *i2c, unsigned char addr);
static int _read_int(I2C_T *i2c, unsigned char addr);
static unsigned short grove_barometer_readut(I2C_T *i2c);
static unsigned long grove_barometer_readup(I2C_T *i2c);




//local variables
static unsigned char cmdbuf[2];
static unsigned char databuf[2];
static const unsigned char OSS = 0;
static short ac1, ac2, ac3;
static unsigned short ac4, ac5, ac6;
static short b1, b2;
static short mb, mc, md;
static long PressureCompensate;
static long _pressure;


void grove_barometer_init(I2C_T *i2c, int pinsda, int pinscl)
{
    suli_i2c_init(i2c, pinsda, pinscl);
}

// Read 1 byte from the BMP085
static char _read_char(I2C_T *i2c, unsigned char addr)
{
	suli_i2c_write(i2c, BMP085_ADDRESS, &addr, 1);
	suli_i2c_read(i2c, BMP085_ADDRESS, databuf, 1);
	return databuf[0];
}

// Read 2 bytes from the BMP085
static int _read_int(I2C_T *i2c, unsigned char addr)
{
	suli_i2c_write(i2c, BMP085_ADDRESS, &addr, 1);
	suli_i2c_read(i2c, BMP085_ADDRESS, databuf, 2);
	return (databuf[0] << 8) + databuf[1];
}

bool grove_barometer_write_setup(I2C_T *i2c)
{
	ac1 = _read_int(i2c, 0xAA);
	ac2 = _read_int(i2c, 0xAC);
	ac3 = _read_int(i2c, 0xAE);
	ac4 = _read_int(i2c, 0xB0);
	ac5 = _read_int(i2c, 0xB2);
	ac6 = _read_int(i2c, 0xB4);
	b1 = _read_int(i2c, 0xB6);
	b2 = _read_int(i2c, 0xB8);
	mb = _read_int(i2c, 0xBA);
	mc = _read_int(i2c, 0xBC);
	md = _read_int(i2c, 0xBE);
	
    return true;
}

// Read the uncompensated temperature value
static unsigned short grove_barometer_readut(I2C_T *i2c)
{
    unsigned short ut;
	
//    Wire.beginTransmission(BMP085_ADDRESS);
//    Wire.write(0xF4);
//    Wire.write(0x2E);
//    Wire.endTransmission();
	cmdbuf[0] = 0xF4;
	cmdbuf[1] = 0x2E;
	suli_i2c_write(i2c, BMP085_ADDRESS, cmdbuf, 2);  // POWER UP
	
	
    suli_delay_ms(5);
    //ut = bmp085ReadInt(0xF6);
	ut = _read_int(i2c, 0xF6);
	
    return ut;
}

// Read the uncompensated pressure value
static unsigned long grove_barometer_readup(I2C_T *i2c)
{
    unsigned char msb, lsb, xlsb;
    unsigned long up = 0;
	
//    Wire.beginTransmission(BMP085_ADDRESS);
//    Wire.write(0xF4);
//    Wire.write(0x34 + (OSS<<6));
//    Wire.endTransmission();
	cmdbuf[0] = 0xF4;
	cmdbuf[1] = 0x34 + (OSS<<6);
	suli_i2c_write(i2c, BMP085_ADDRESS, cmdbuf, 2);  // POWER UP
	
	
    suli_delay_ms(2 + (3<<OSS));

    // Read register 0xF6 (MSB), 0xF7 (LSB), and 0xF8 (XLSB)
//    msb = bmp085Read(0xF6);
//    lsb = bmp085Read(0xF7);
//    xlsb = bmp085Read(0xF8);
	 msb = _read_char(i2c, 0xF6);
    lsb = _read_char(i2c, 0xF7);
    xlsb = _read_char(i2c, 0xF8);
	
    up = (((unsigned long) msb << 16) | ((unsigned long) lsb << 8) | (unsigned long) xlsb) >> (8-OSS);
	
    return up;
}

bool grove_barometer_gettemperature(I2C_T *i2c, float *temperature)
{
    long x1, x2;
	unsigned short ut = grove_barometer_readut(i2c);
	
    x1 = (((long)ut - (long)ac6)*(long)ac5) >> 15;
    x2 = ((long)mc << 11)/(x1 + md);
    PressureCompensate = x1 + x2;

    float temp = ((PressureCompensate + 8)>>4);
    *temperature = temp /10;
	
	return true;
}

bool grove_barometer_getpressure(I2C_T *i2c, long *pressure)
{
    long x1, x2, x3, b3, b6, p;
    unsigned long b4, b7;
	unsigned long up = grove_barometer_readup(i2c);
	
    b6 = PressureCompensate - 4000;
    x1 = (b2 * (b6 * b6)>>12)>>11;
    x2 = (ac2 * b6)>>11;
    x3 = x1 + x2;
    b3 = (((((long)ac1)*4 + x3)<<OSS) + 2)>>2;

    // Calculate B4
    x1 = (ac3 * b6)>>13;
    x2 = (b1 * ((b6 * b6)>>12))>>16;
    x3 = ((x1 + x2) + 2)>>2;
    b4 = (ac4 * (unsigned long)(x3 + 32768))>>15;

    b7 = ((unsigned long)(up - b3) * (50000>>OSS));
    if (b7 < 0x80000000)
    p = (b7<<1)/b4;
    else
    p = (b7/b4)<<1;

    x1 = (p>>8) * (p>>8);
    x1 = (x1 * 3038)>>16;
    x2 = (-7357 * p)>>16;
    p += (x1 + x2 + 3791)>>4;

    _pressure = p;
	*pressure = _pressure;
    return true;
}

bool grove_barometer_calcaltitude(I2C_T *i2c, float *altitude)
{
    float A = _pressure/101325;
    float B = 1/5.25588;
    float C = pow(A,B);
    C = 1 - C;
    C = C /0.0000225577;
	*altitude = C;
    return true;
}

