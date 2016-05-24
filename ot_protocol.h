#ifndef __PROTOCOL_H
#define __PROTOCOL_H

#include <inttypes.h>
#include <string.h>
#include <stddef.h>

typedef struct ot_telem_data {
	char* time;
	char* latitude;
	char* longitude;
	char* altitude;
	char* speed;
	char* bearing;
} ot_telem_data_t;

uint32_t ot_crc_update(uint32_t crc, uint8_t data);
uint32_t ot_crc_string(char *s);

uint16_t ot_crc_xmodem_update (uint16_t crc, uint8_t data);
uint16_t ot_crc16_checksum (char *string);

void ot_telemetry_string_start(char* ts, int id, char* callsign, ot_telem_data_t basic_data);
void ot_telemetry_string_add_data( char* ts, char* data);
void ot_telemetry_string_end(char* ts);

#endif
