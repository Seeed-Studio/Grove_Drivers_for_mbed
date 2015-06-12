


#ifndef __GROVE_RELAY_H__
#define __GROVE_RELAY_H__

#include "suli2.h"

//GROVE_NAME        "Grove_Relay"
//IF_TYPE           GPIO
//IMAGE_URL         http://www.seeedstudio.com/depot/bmz_cache/d/df3ef3f9ba7f58333235895c0d3c4fb2.image.530x397.jpg


class GroveRelay
{
public:
    GroveRelay(int pin);
    bool write_onoff(int onoff);
private:
    IO_T *io;
};


#endif
