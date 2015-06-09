


#ifndef __GROVE_TEMP_HUM_CLASS_H__
#define __GROVE_TEMP_HUM_CLASS_H__

#include "grove_temp_hum.h"

//GROVE_NAME        "Grove_TempHum"
//IF_TYPE           GPIO
//IMAGE_URL         http://www.seeedstudio.com/wiki/File:Temp%26Humi.jpg

class GroveTempHum
{
public:
    GroveTempHum(int pin);
    bool write_setup(uint8_t type, uint8_t count);
	bool read_temperature(bool S, float *temperature);
	bool read_humidity(float *humidity);

private:
    IO_T *io;
};

#endif
