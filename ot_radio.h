/*
   Copyright (c) 2016 - David Pello, ladecadence.net

   Permission is hereby granted, free of charge, to any person obtaining a copy
   of this software and associated documentation files (the "Software"), to deal
   in the Software without restriction, including without limitation the rights
   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
   copies of the Software, and to permit persons to whom the Software is
   furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in
   all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
   THE SOFTWARE.

*/

#include <inttypes.h>

#ifndef _OT_RADIO_H
#define _OT_RADIO_H

/******* LIBRARY CONFIGURATION *******/
#define CPU_CLOCK           16000000 
#define OT_RADIO_EN_PIN        P1_6
#define OT_RADIO_DATA_PIN      P2_0
/******* CONFIGURATION END *******/

#ifndef CPU_CLOCK
#error "You have to define CPU_CLOCK in Hz"
#endif

uint8_t ot_radio_initialized = 0;

void ot_radio_init();
void ot_radio_enable();
void ot_radio_disable();

#endif
