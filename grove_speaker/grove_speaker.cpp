/*
 * grove_speaker.cpp
 *
 * Copyright (c) 2012 seeed technology inc.
 * Website    : www.seeed.cc
 * Author     : Jacky Zhang (qi.zhang@seeed.cc)
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

#include "suli2.h"
#include "grove_speaker.h"

#define USE_DEBUG (1)

GroveSpeaker::GroveSpeaker(int pin)
{
    this->io = (IO_T *)malloc(sizeof(IO_T));

    suli_pin_init(this->io, pin, SULI_OUTPUT);
    suli_pin_write(this->io, SULI_LOW);
}

//duration: the time sounds, unit: ms
//freq: the frequency of speaker, unit: Hz
bool GroveSpeaker::write_sound(int freq, int duration)
{  
    if(freq == 0 || duration == 0) return;
	
	uint32_t interval = (uint32_t)1000000 / freq;//convert the unit to us
	uint32_t times = (uint32_t)duration * 1000 / interval;//calcuate how many times the loop takes
#if USE_DEBUG
	Serial1.print("interval");
	Serial1.println(interval);
	Serial1.print("times");
	Serial1.println(times);
#endif
	for(int i=0; i<times; i++)
 	{
		suli_pin_write(this->io, SULI_HIGH);
		suli_delay_us(interval);
		suli_pin_write(this->io, SULI_LOW);
		suli_delay_us(interval);
	}
	
    return true;
}

