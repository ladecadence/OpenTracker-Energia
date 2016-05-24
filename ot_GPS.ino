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

#include <stdlib.h>
#include "ot_utils.h"

char ot_gps_buffer[128];

void ot_gps_init(int baudrate) {
  Serial1.begin(baudrate);
  ot_gps_data = (ot_nmea_data_t)malloc(sizeof(struct ot_nmea_data_struct));
}

void ot_gps_convert_degrees(char* coord)
{
  float temp;
  uint16_t deg;
  float minut;
  int32_t decminut;

  // convert to float
  temp = ot_atof(coord);

  deg = temp / 100.0f;
  minut = temp - (deg * 100.0f);
  minut = minut / 60.0f;
  minut = minut * 100000000;
  decminut = (int32_t) minut;

  sprintf(coord, "%d.%ld", deg, decminut);

}

void ot_gps_get_sentence() {
  char c = 0;
  int count = 0;
  while (c != '\n' && count < 127) {
    if (Serial1.available()) {
      c = Serial1.read();
      ot_gps_buffer[count] = c;
      count++;
    }
    ot_gps_buffer[count+1] = 0;
  }
}

/* parses nmea GGA string filling fields of data structure */
int ot_gps_parse_gga(ot_nmea_data_t data, char* packet)
{

  uint8_t i;
  uint8_t gpindex=0;

  /* start after $GPGGA, */
  i=7;

  if((packet[i]==',') & (packet[i+1]==',')) /* empty? */
    return 1; /* error */

  /* time */
  while(packet[i] != ',')	{
    data->time[gpindex]=packet[i];
    i++;
    gpindex++;
  }		
  data->time[gpindex]='\0'; /* end of string */

  i++;
  gpindex=0;

  /* latitude */
  while(packet[i] != ',')
  {
    data->latitude[gpindex]=packet[i];
    i++;
    gpindex++;
  }		
  data->latitude[gpindex]='\0';

  i++;
  gpindex=0;

  /* N/S */
  while(packet[i] != ',')
  {
    data->ns[gpindex]=packet[i];
    i++;
    gpindex++;
  }		
  data->ns[gpindex]='\0';

  i++;
  gpindex=0;

  /* longitude */
  while(packet[i] != ',')
  {
    data->longitude[gpindex]=packet[i];
    i++;
    gpindex++;
  }		
  data->longitude[gpindex]='\0';

  i++;
  gpindex=0;

  /* E/W */
  while(packet[i] != ',')
  {
    data->ew[gpindex]=packet[i];
    i++;
    gpindex++;
  }		
  data->ew[gpindex]='\0';

  i++;
  gpindex=0;

  /* fix quality */
  while(packet[i] != ',')
  {
    data->fix_quality[gpindex]=packet[i];
    i++;
    gpindex++;
  }
  data->fix_quality[gpindex]='\0';	

  i++;
  gpindex=0;

  /* number of satellites */
  while(packet[i] != ',')
  {
    data->num_sats[gpindex]=packet[i];
    i++;
    gpindex++;
  }		
  data->num_sats[gpindex]='\0';

  i++;
  gpindex=0;

  /* horizontal dilution */
  while(packet[i] != ',')
  {
    /* do nothing */
    i++;
    gpindex++;
  }		

  i++;
  gpindex=0;

  /* altitude */
  while(packet[i] != ',')
  {
    data->altitude[gpindex]=packet[i];
    i++;
    gpindex++;
  }		
  data->altitude[gpindex]='\0';

  i++;
  gpindex=0;

  /* reached here, nice! */

  /* Ivalid data if fix is 0 */
  int n = atoi(data->fix_quality);
  if (n == 0)
    return 1;

  /* convert coordinates */
  ot_gps_convert_degrees(data->latitude);
  ot_gps_convert_degrees(data->longitude);	

  return 0;
}

int ot_gps_update() {
  int r;
  ot_gps_get_sentence();
  // GGA ?
  while (!(ot_gps_buffer[4] == 'G' && ot_gps_buffer[5] == 'A')) {
    ot_led_blink();
    ot_gps_get_sentence();
  }
   
  // Ok GGA
  r = ot_gps_parse_gga(ot_gps_data, ot_gps_buffer);
  return r;
}


