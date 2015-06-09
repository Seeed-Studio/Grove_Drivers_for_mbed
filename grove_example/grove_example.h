


#ifndef __GROVE_EXAMPLE_H__
#define __GROVE_EXAMPLE_H__

#include "suli2.h"

void grove_example_init(I2C_T *i2c, int pinsda, int pinscl);

bool grove_example_read_temp(I2C_T *i2c, int *temp);

bool grove_example_read_uint8_value(I2C_T *i2c, uint8_t *value);

bool grove_example_read_humidity(I2C_T *i2c, float *humidity);

bool grove_example_read_acc(I2C_T *i2c, float *ax, float *ay, float *az);

bool grove_example_read_compass(I2C_T *i2c, float *cx, float *cy, float *cz, int *degree);

bool grove_example_read_with_arg(I2C_T *i2c, float *cx, float *cy, float *cz, int *degree, int arg);

bool grove_example_write_acc_mode(I2C_T *i2c, uint8_t mode);

bool grove_example_write_float_value(I2C_T *i2c, float f);

bool grove_example_write_multi_value(I2C_T *i2c, int a, float b, uint32_t c);

bool grove_example_attach_event_handler(CALLBACK_T handler);

void _grove_example_internal_function(I2C_T *i2c, float x);

void _trigger();

#endif
