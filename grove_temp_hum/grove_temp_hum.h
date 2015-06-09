


#ifndef __GROVE_TEMP_HUM_H__
#define __GROVE_TEMP_HUM_H__

#include "suli2.h"

// how many timing transitions we need to keep track of. 2 * number bits + extra
#if defined(__MBED__)
#define MAXTIMINGS 85
#elif defined(ARDUINO)
#define MAXTIMINGS 85
#endif

#define DHT11 11
#define DHT22 22
#define DHT21 21
#define AM2301 21

void grove_temp_hum_init(IO_T *io, int pin);
bool grove_temp_hum_write_setup(IO_T *io, uint8_t type, uint8_t count);
bool grove_temp_hum_readtemperature(IO_T *io, bool S, float *temperature);
bool grove_temp_hum_readhumidity(IO_T *io, float *humidity);

#endif
