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

#ifndef _OT_GPS_H
#define _OT_GPS_H

#define OT_GPS_BAUDRATE  4800

struct ot_nmea_data_struct {
	char time[11];
	char latitude[16];
	char longitude[16];
	char ns[2];
	char ew[2];
	char fix_quality[2];
	char num_sats[3];
	char altitude[8];
};

typedef struct ot_nmea_data_struct* ot_nmea_data_t;
ot_nmea_data_t ot_gps_data;

void ot_gps_init(int baudrate);
void ot_gps_convert_degrees(char* coord);
void ot_gps_get_sentence();
int ot_gps_parse_gga(ot_nmea_data_t data, char* packet);
int ot_gps_update();

#endif
