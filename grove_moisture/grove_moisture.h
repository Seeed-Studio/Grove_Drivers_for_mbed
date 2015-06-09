


#ifndef __GROVE_MOISTURE_H__
#define __GROVE_MOISTURE_H__

#include "suli2.h"

void grove_moisture_init(ANALOG_T *analog, int pin);
bool grove_moisture_write_setup(ANALOG_T *analog);
bool grove_moisture_readmoisture(ANALOG_T *analog, uint16_t *moisture);

#endif
