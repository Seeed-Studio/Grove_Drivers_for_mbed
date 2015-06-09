


#ifndef __GROVE_MOISTURE_CLASS_H__
#define __GROVE_MOISTURE_CLASS_H__

#include "grove_moisture.h"

//GROVE_NAME        "Grove_Moisture"
//IF_TYPE           ANALOG
//IMAGE_URL         http://www.seeedstudio.com/wiki/File:Moisture_sensor_.jpg

class GroveMoisture
{
public:
    GroveMoisture(int pin);
    bool write_setup(void);
    bool read_moisture(uint16_t *moisture);
    
private:
    ANALOG_T *analog;
};

#endif
