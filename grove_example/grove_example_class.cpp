

#include "grove_example_class.h"

GroveExample::GroveExample(int pinsda, int pinscl)
{
    this->i2c = (I2C_T *)malloc(sizeof(I2C_T));
    grove_example_init(this->i2c, pinsda, pinscl);
}

bool GroveExample::read_temp(int *temp)
{
    return grove_example_read_temp(this->i2c, temp);
}

bool GroveExample::read_uint8_value(uint8_t *value)
{
    return grove_example_read_uint8_value(this->i2c, value);
}

bool GroveExample::read_humidity(float *humidity)
{
    return grove_example_read_humidity(this->i2c, humidity);
}

bool GroveExample::read_acc(float *ax, float *ay, float *az)
{
    return grove_example_read_acc(this->i2c, ax, ay, az);
}

bool GroveExample::read_compass(float *cx, float *cy, float *cz, int *degree)
{
    return grove_example_read_compass(this->i2c, cx, cy, cz, degree);
}

bool GroveExample::read_with_arg(float *cx, float *cy, float *cz, int *degree, int arg)
{
    return grove_example_read_with_arg(this->i2c, cx, cy, cz, degree, arg);
}

bool GroveExample::write_acc_mode(uint8_t mode)
{
    return grove_example_write_acc_mode(this->i2c, mode);
}

bool GroveExample::write_float_value(float f)
{
    return grove_example_write_float_value(this->i2c, f);
}

bool GroveExample::write_multi_value(int a, float b, uint32_t c)
{
    return grove_example_write_multi_value(this->i2c, a, b, c);
}

bool GroveExample::attach_event_handler(CALLBACK_T handler)
{
    return grove_example_attach_event_handler(handler);
}
