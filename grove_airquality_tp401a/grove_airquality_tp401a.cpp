/*
 * grove_comp_hmc5883l.cpp
 *
 * Copyright (c) 2012 seeed technology inc.
 * Website    : www.seeed.cc
 * Author     : Jacky Zhang
 *
 * The MIT License (MIT)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */


#include "grove_airquality_tp401a.h"

#define USE_DEBUG (1)

GroveAirquality::GroveAirquality(int pin)
{
    this->analog = (ANALOG_T *)malloc(sizeof(ANALOG_T));
    suli_analog_init(this->analog, pin);
    _init();
}

void GroveAirquality::_init(void)
{
    uint32_t time = 0;
    int adc_value;
    
    is_sensor_exist = false;
    while(1)
    {
        adc_value = suli_analog_read(analog);
#if USE_DEBUG
        Serial1.print("adc_value: ");
        Serial1.println(adc_value);
#endif
        if(adc_value > 20 && adc_value < 798)//if the sensor is exist, the ADC value should be in a range
        {
            inited_time = suli_millis();//get the time point when sensor is detected.
            is_sensor_exist = true;//flag: the sonsor is exist
#if USE_DEBUG
            Serial1.println("the sonsor is exist");
#endif
            return;
        }
        delay(50);//wait for sensor connected
        time += 50;
        if(time > 10000)//time out, 10s
        {
            is_sensor_exist = false;//flag: the sonsor is not exist
#if USE_DEBUG
             Serial1.println("time out, 10s");
#endif
            return;
        }  
    }
}

bool GroveAirquality::read_quality(int *quality)
{
    //judge if the sensor is exist
    if(is_sensor_exist != true)
    {
#if USE_DEBUG
        Serial1.println("the sonsor is not exist");
#endif
        return false;
    }
        
        
    //judge if the sensor is prepared OK
    uint32_t now = suli_millis();
    if(now - inited_time < 20000)//the sensor is heating now, it can be used after 20s.
    {
#if USE_DEBUG
        Serial1.println("wait for a while");
#endif
        return false;
    }
    
    //get AD value
    *quality = suli_analog_read(analog);
    
    return true;
}
