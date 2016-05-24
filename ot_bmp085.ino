#include "ot_bmp085.h"
#include "ot_utils.h"

char ot_bmp085_read(unsigned char address)
{
	unsigned char data; 

	/* i2c start condition */
	ot_i2c.beginTransmission(OT_BMP085_ADDRESS);
	/* sends register address */
	ot_i2c.write(byte(address));
	/* i2c stop condition */
	ot_i2c.endTransmission();

	/* reads byte */
	ot_i2c.beginTransmission(OT_BMP085_ADDRESS);
	ot_i2c.requestFrom(OT_BMP085_ADDRESS,1); /* read command */
	data = ot_i2c.read();
	ot_i2c.endTransmission();

	return data;
}

int ot_bmp085_read_int(unsigned char address)
{
	int data; 

	/* i2c start condition */
	ot_i2c.beginTransmission(OT_BMP085_ADDRESS);

	/* sends register address */
	ot_i2c.write(byte(address));
	/* i2c stop condition */
	ot_i2c.endTransmission();

	/* reads int */
	ot_i2c.beginTransmission(OT_BMP085_ADDRESS);
	ot_i2c.requestFrom(OT_BMP085_ADDRESS,2); /* read command */
	data = ot_i2c.read();
        data <<= 8;
        data |= ot_i2c.read();
	ot_i2c.endTransmission();

	return data;
}

void ot_bmp085_calibration(void)
{
	ac1 = ot_bmp085_read_int(0xAA);
	ac2 = ot_bmp085_read_int(0xAC);
	ac3 = ot_bmp085_read_int(0xAE);
	ac4 = ot_bmp085_read_int(0xB0);
	ac5 = ot_bmp085_read_int(0xB2);
	ac6 = ot_bmp085_read_int(0xB4);
	b1 = ot_bmp085_read_int(0xB6);
	b2 = ot_bmp085_read_int(0xB8);
	mb = ot_bmp085_read_int(0xBA);
	mc = ot_bmp085_read_int(0xBC);
	md = ot_bmp085_read_int(0xBE);
}

unsigned int ot_bmp085_read_utemperature(void)
{
	unsigned int ut;

	/* writing 0x2E into register 0xF4 requests a temperature reading */
	ot_i2c.beginTransmission(OT_BMP085_ADDRESS);
	ot_i2c.write(byte(0xF4));
	ot_i2c.write(byte(0x2E));
	ot_i2c.endTransmission();

	/* wait at least 4.5ms */
	delay(5);

	ut = ot_bmp085_read_int(0xF6);

	return ut;
}

long ot_bmp085_read_temperature(void)
{
	long x1, x2;
	  
	x1 = (((long)ot_bmp085_read_utemperature() - (long)ac6)*(long)ac5) >> 15;
	x2 = ((long)mc << 11)/(x1 + md);
	b5 = x1 + x2;

	return ((b5 + 8)>>4);  
}

unsigned int ot_bmp085_read_upressure(void)
{
	unsigned char data[3];
	unsigned long up = 0;

	/* writing 0x34+(oversampling<<6) into register 0xF4 requests */ 
	/* a pressure reading with oversampling setting */
	ot_i2c.beginTransmission(OT_BMP085_ADDRESS);
	ot_i2c.write(byte(0xF4));
	ot_i2c.write(byte(0x34 + (OT_BMP085_OVERSAMPLING<<6)));
	ot_i2c.endTransmission();

	/* wait for conversion, depends on oversampling */
	delay(2 + (3<<OT_BMP085_OVERSAMPLING));

	/* read register 0xF6 (MSB), 0xF7 (LSB), and 0xF8 (XLSB) */
	ot_i2c.beginTransmission(OT_BMP085_ADDRESS);
	ot_i2c.write(byte(0xF6));
	ot_i2c.endTransmission();

	ot_i2c.beginTransmission(OT_BMP085_ADDRESS);
	ot_i2c.requestFrom(OT_BMP085_ADDRESS,3); /* read */

        data[0] = ot_i2c.read();
        data[1] = ot_i2c.read();
        data[2] = ot_i2c.read();

	up = (((unsigned long) data[0] << 16) | ((unsigned long) data[1] << 8) | (unsigned long) data[2]) >> (8-OT_BMP085_OVERSAMPLING);

	return up;
}


long ot_bmp085_read_pressure(void)
{
  long x1, x2, x3, b3, b6, p;
  unsigned long b4, b7;
  
  b6 = b5 - 4000;
  // Calculate B3
  x1 = (b2 * (b6 * b6)>>12)>>11;
  x2 = (ac2 * b6)>>11;
  x3 = x1 + x2;
  b3 = (((((long)ac1)*4 + x3)<<OT_BMP085_OVERSAMPLING) + 2)>>2;
  
  // Calculate B4
  x1 = (ac3 * b6)>>13;
  x2 = (b1 * ((b6 * b6)>>12))>>16;
  x3 = ((x1 + x2) + 2)>>2;
  b4 = (ac4 * (unsigned long)(x3 + 32768))>>15;
  
  b7 = ((unsigned long)(ot_bmp085_read_upressure()-b3) * (50000>>OT_BMP085_OVERSAMPLING));
  if (b7 < 0x80000000)
    p = (b7<<1)/b4;
  else
    p = (b7/b4)<<1;
    
  x1 = (p>>8) * (p>>8);
  x1 = (x1 * 3038)>>16;
  x2 = (-7357 * p)>>16;
  p += (x1 + x2 + 3791)>>4;
  
  return p;
}



