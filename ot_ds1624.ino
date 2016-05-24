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

#include "ot_ds1624.h"


void ot_ds1624_init(int addr) {
  ot_i2c.beginTransmission(addr);     // transmit to device 
                                            // device address is specified in datasheet
  ot_i2c.write(byte(0xAC));                        // sends instruction byte  
  ot_i2c.write(byte(OT_DS1624_CONTINUOUS_CONVERSION)); // continuos conversion mode  
  ot_i2c.endTransmission();                   // stop transmitting
  delay(100);
  ot_i2c.beginTransmission(addr);
  ot_i2c.write(byte(OT_DS1624_CONVERT_T));            //Enable the continuos conversion mode
  ot_i2c.endTransmission();
}

float ot_ds1624_get_temp(int addr)
{
  float temperature = 0;
  int tempmsb = 0;
  int templsb = 0;
  int temp2 = 0;

  ot_i2c.beginTransmission(addr);
  ot_i2c.write(byte(OT_DS1624_READ_T));
  ot_i2c.requestFrom(addr, 2);

  if (ot_i2c.available()) {
    tempmsb = ot_i2c.read();
  }
  if (ot_i2c.available()) {
    templsb = ot_i2c.read();
  }
  temp2 = templsb >> 3;
  temperature = (float(tempmsb) + (float(temp2) * 0.03125));
  ot_i2c.endTransmission();
  return temperature;
}
