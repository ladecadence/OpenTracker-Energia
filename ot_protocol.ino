#include <inttypes.h>
#include "ot_protocol.h"

static uint32_t ot_crc_table[16] = {
	0x00000000, 0x1db71064, 0x3b6e20c8, 0x26d930ac,
	0x76dc4190, 0x6b6b51f4, 0x4db26158, 0x5005713c,
	0xedb88320, 0xf00f9344, 0xd6d6a3e8, 0xcb61b38c,
	0x9b64c2b0, 0x86d3d2d4, 0xa00ae278, 0xbdbdf21c
};

uint32_t ot_crc_update(uint32_t crc, uint8_t data)
{
	uint8_t tbl_idx;
	tbl_idx = crc ^ (data >> (0 * 4));
	crc = ot_crc_table[(tbl_idx & 0x0f)] ^ (crc >> 4);
	tbl_idx = crc ^ (data >> (1 * 4));
	crc = ot_crc_table[(tbl_idx & 0x0f)] ^ (crc >> 4);
	return crc;
};

uint32_t ot_crc_string(char *s)
{
	uint32_t crc = ~0L;
	while (*s)
		crc = ot_crc_update(crc, *s++);
	crc = ~crc;
	return crc;
}

uint16_t ot_crc_xmodem_update (uint16_t crc, uint8_t data)
{
	int i;
	crc = crc ^ ((uint16_t)data << 8);
	for (i=0; i<8; i++)
	{
		if (crc & 0x8000)
			crc = (crc << 1) ^ 0x1021;
		else
			crc <<= 1;
	}
	return crc;
}


uint16_t ot_crc16_checksum (char *string)
{
	size_t i;
	uint16_t crc;
	uint8_t c;

	crc = 0xFFFF;

	// Calculate checksum ignoring the first two $s
	for (i = 2; i < strlen(string); i++)
	{
		c = string[i];
		crc = ot_crc_xmodem_update (crc, c);
	}

	return crc;
}

