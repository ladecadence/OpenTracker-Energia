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

#include "msp430.h"
#include "ot_radio.h"

#ifndef _OT_RTTY_H
#define _OT_RTTY_H

/******* LIBRARY CONFIGURATION *******/
#define OT_RTTY_BAUDRATE       OT_RTTY_BAUDRATE_100
#define OT_RTTY_ASCII          OT_RTTY_ASCII_8
/******* CONFIGURATION END *******/


#define OT_RTTY_BAUDRATE_45    22220
#define OT_RTTY_BAUDRATE_50    20100
#define OT_RTTY_BAUDRATE_100   10050
#define OT_RTTY_BAUDRATE_150   6720
#define OT_RTTY_BAUDRATE_300   3370
#define OT_RTTY_BAUDRATE_600   1680
#define OT_RTTY_ASCII_7        7
#define OT_RTTY_ASCII_8        8

#define OT_RTTY_MARK           60
#define OT_RTTY_SPACE          50

int ot_rtty_baudrate;
int ot_rtty_bits;

void ot_rtty_init();
void ot_rtty_txbit(int bit);
void ot_rtty_txbyte(char c);
void ot_rtty_txstring(char * string);
void ot_rtty_send_temperature(float t);
void ot_rtty_send_pressure(long p);

#endif
