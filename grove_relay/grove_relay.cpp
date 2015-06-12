

#include "suli2.h"
#include "grove_relay.h"

GroveRelay::GroveRelay(int pin)
{
    this->io = (IO_T *)malloc(sizeof(IO_T));

    suli_pin_init(io, pin, SULI_OUTPUT);
}

bool GroveRelay::write_onoff(int onoff)
{
    suli_pin_write(io, onoff);
    return true;
}

