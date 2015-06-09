

#include "suli2.h"
#include "grove_moisture.h"



//local functions


//local variables




void grove_moisture_init(ANALOG_T *analog, int pin)
{
	suli_analog_init(analog, pin);
}

bool grove_moisture_write_setup(ANALOG_T *analog)
{
    return true;
}

bool grove_moisture_readmoisture(ANALOG_T *analog, uint16_t *moisture)
{
	*moisture = suli_analog_read(analog);
	return true;
}

