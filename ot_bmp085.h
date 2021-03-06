#ifndef _OT_BMP085_H
#define _OT_BMP085_H

#define OT_BMP085_ADDRESS 0x77
#define OT_BMP085_OVERSAMPLING 0

/* Calibration values */
int ac1;
int ac2; 
int ac3; 
unsigned int ac4;
unsigned int ac5;
unsigned int ac6;
int b1; 
int b2;
int mb;
int mc;
int md;
long b5; 

/* reads 1 byte from bmp085 */
char ot_bmp085_read(unsigned char address);

/* reads 2 bytes from bmp085 */
/* first byte from address, second from address+1 */
int ot_bmp085_read_int(unsigned char address);

/* reads bmp085 calibration values */
void ot_bmp085_calibration(void);

/* reads uncalibrated temperature */
unsigned int ot_bmp085_read_utemperature(void);

/* reads temperature */
long ot_bmp085_read_temperature(void);

/* reads uncalibrated pressure */
unsigned int ot_bmp085_read_upressure(void);

/* reads pressure */
long ot_bmp085_read_pressure(void);


#endif
