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

#include <string.h>

#include "ot_protocol.h"
#include "ot_GPS.h"
#include "ot_utils.h"
#include "ot_i2c.h"
#include "ot_ds1624.h"

#define TELEM_SIZE 120
#define ID "ASHAB NS2"
#define QRA "EA1IDZ"

char* telem_msg;
int gps_error;
uint32_t cycles_counter;
uint16_t crc;
char crcs[6];
char data_id[8];

void setup()
{
  ot_led_init();
  ot_gps_init(4800);
  ot_i2c.begin();
  ot_ds1624_init(OT_DS1624_ADDR);
  ot_radio_init();
  ot_dominoex_init();
  Serial.begin(19200);
  
  /* Init variables */
  telem_msg = (char*) malloc(TELEM_SIZE * sizeof(char));
  cycles_counter = 0;
  
}

void loop()
{
  
  // clear telemetry string
  memset(telem_msg, 0, TELEM_SIZE * sizeof(char));
  
  /* add linefeed */
  strncat(telem_msg, "\n\n", 2);
  /* add string start */
  strncat(telem_msg, "$$", 2);

  //Add ID and QRA to telemetry msg;
  strncat(telem_msg, ID, strlen(ID));
  strncat(telem_msg, "/", 1);
  strncat(telem_msg, QRA, strlen(QRA));
  strncat(telem_msg, ",", 1);
  // Add string ID
  sprintf(data_id, "%lu", cycles_counter);
  strncat(telem_msg, data_id, strlen(data_id));
  strncat(telem_msg, ",", 1);
  
  
  gps_error=1;
  gps_error = ot_gps_update();

  if (!gps_error) {
      strncat(telem_msg, ot_gps_data->time, strlen(ot_gps_data->time));
      strncat(telem_msg, ",", 1);
      strncat(telem_msg, ot_gps_data->latitude, strlen(ot_gps_data->latitude));      
      strncat(telem_msg, ot_gps_data->ns, strlen(ot_gps_data->ns));
      strncat(telem_msg, ",", 1);
      strncat(telem_msg, ot_gps_data->longitude, strlen(ot_gps_data->longitude));  
      strncat(telem_msg, ot_gps_data->ew, strlen(ot_gps_data->ew));
      strncat(telem_msg, ",", 1);
      strncat(telem_msg, ot_gps_data->altitude, strlen(ot_gps_data->altitude));
      strncat(telem_msg, ",", 1);

  }
  else
  {
      strncat(telem_msg, "GPS Data invalid", strlen("GPS Data invalid"));
      strncat(telem_msg, " FQ: ", strlen(" FQ: "));
      strncat(telem_msg, ot_gps_data->fix_quality, strlen(ot_gps_data->fix_quality));
      strncat(telem_msg, ",", 1);
  }
  
  
  // calculate and append CRC
  crc = ot_crc16_checksum(telem_msg);
  sprintf(crcs, "*%04X", crc);
  strncat(telem_msg, crcs, strlen(crcs));
  // append EOL
  strncat(telem_msg, "\n\n", 2);
  
  ot_dominoex_reset();
  ot_radio_enable();
  delay(2000);
  //ot_dominoex_txid("-ASHAB NS2-");
  ot_dominoex_txstring(telem_msg);
  delay(1000);
  ot_radio_disable();
  
  cycles_counter++;  

}
