
#include "suli2.h"
#include "grove_acc_mma7660.h"

GroveAccMMA7660::GroveAccMMA7660(int pinsda, int pinscl)
{
    this->i2c = (I2C_T *)malloc(sizeof(I2C_T));
    suli_i2c_init(this->i2c, pinsda, pinscl);
    _setmode(MMA7660_STAND_BY);
    _setsamplerate(AUTO_SLEEP_120);
    _setmode(MMA7660_ACTIVE);
    uint8_t r = (0x7 << 5);
    suli_i2c_write_reg(i2c, MMA7660_ADDR, MMA7660_INTSU, &r, 1); //enable shake detection on 3 axises.
}

void GroveAccMMA7660::_setmode(uint8_t mode)
{
    suli_i2c_write_reg(i2c, MMA7660_ADDR, MMA7660_MODE, &mode, 1);
}

void GroveAccMMA7660::_setsamplerate(uint8_t rate)
{
    suli_i2c_write_reg(i2c, MMA7660_ADDR, MMA7660_SR, &rate, 1);
}

void GroveAccMMA7660::_getxyz(int8_t *x, int8_t *y, int8_t *z)
{
    uint8_t val[3];

    do
    {
        suli_i2c_read_reg(i2c, MMA7660_ADDR, MMA7660_X, val, 3);
    }
    while (val[0]>63 || val[1]>63 || val[2]>63);

    Serial1.println("raw: ");
    Serial1.println(val[0]);
    Serial1.println(val[1]);
    Serial1.println(val[2]);

    *x = ((int8_t)(val[0] << 2)) / 4;
    *y = ((int8_t)(val[1] << 2)) / 4;
    *z = ((int8_t)(val[2] << 2)) / 4;
}

bool GroveAccMMA7660::read_accelerometer(float *ax, float *ay, float *az)
{
    int8_t x,y,z;
    _getxyz(&x,&y,&z);
    *ax = x/21.00;
    *ay = y/21.00;
    *az = z/21.00;

    return true;
}

bool GroveAccMMA7660::read_shacked(uint8_t *shacked)
{
    uint8_t r;
    do
    {
        suli_i2c_read_reg(i2c, MMA7660_ADDR, MMA7660_TILT, &r, 1);
    } while ((r&0x40)>0);

    if (r&0x80)
    {
        *shacked = 1;
    } else
    {
        *shacked = 0;
    }
    return true;
}


