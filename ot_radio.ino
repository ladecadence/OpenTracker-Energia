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

#include "ot_radio.h"

void ot_radio_init()
{
    /* set pins */
    pinMode(OT_RADIO_EN_PIN, OUTPUT);
    pinMode(OT_RADIO_DATA_PIN, OUTPUT);

    /* ok, radio ready */
    ot_radio_initialized = 1;

    /* disable output */
    ot_radio_disable();
}

void ot_radio_enable()
{
    digitalWrite(OT_RADIO_EN_PIN, HIGH);
}

void ot_radio_disable()
{
    digitalWrite(OT_RADIO_EN_PIN, LOW);
}
