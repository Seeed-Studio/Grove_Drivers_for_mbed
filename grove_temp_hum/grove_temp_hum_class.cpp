

#include "grove_temp_hum_class.h"

GroveTempHum::GroveTempHum(int pin)
{
    this->io = (IO_T *)malloc(sizeof(IO_T));
    grove_temp_hum_init(this->io, pin);
}

bool GroveTempHum::write_setup(uint8_t type, uint8_t count)
{
    return grove_temp_hum_write_setup(this->io, type, count);
}

bool GroveTempHum::read_temperature(bool S, float *temperature)
{
    return grove_temp_hum_readtemperature(this->io, S, temperature);
}

bool GroveTempHum::read_humidity(float *humidity)
{
    return grove_temp_hum_readhumidity(this->io, humidity);
}
