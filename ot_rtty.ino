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

#include "ot_rtty.h"

void ot_rtty_init()
{
    /* radio initialized? */
    if (!ot_radio_initialized)
        ot_radio_init();
    
    P2SEL |= BIT0;
        
    /* Timer A */
    TA1CCTL1 = OUTMOD_7;                // TOGGLE // TACCR1 reset/set
    TA1CTL = TASSEL_2 + MC_1 + TACLR;   // SMCLK, upmode
    TA1CCR0 = 100-1;                    // Period
        

}

void ot_rtty_txbit (int bit)
{
    /*
     * Sends one bit of data
     *
     */

    if (bit)
    {
        /* mark */
        //RTTY_PORT |= RTTY_MARK_PIN;
        //RTTY_PORT &= ~(RTTY_SPACE_PIN);
        TA1CCR1 = OT_RTTY_MARK-1;
    }
    else
    {
        /* space */
        //RTTY_PORT |= RTTY_SPACE_PIN;
        //RTTY_PORT &= ~(RTTY_MARK_PIN);
        TA1CCR1 = OT_RTTY_SPACE-1;

    }
    delayMicroseconds(OT_RTTY_BAUDRATE/4);
    delayMicroseconds(OT_RTTY_BAUDRATE/4);
    delayMicroseconds(OT_RTTY_BAUDRATE/4);
    delayMicroseconds(OT_RTTY_BAUDRATE/4);
}

void ot_rtty_txbyte (char c)
{
    /* Simple function to sent each bit of a char to 
     ** rtty_txbit function. 
     ** NB The bits are sent Least Significant Bit first
     **
     ** All chars should be preceded with a 0 and 
     ** proceded with a 1. 0 = Start bit; 1 = Stop bit
     **
     */

    int i;

    ot_rtty_txbit (0); /* Start bit */

    /* Send bits for for char LSB first */
    for (i = 0; i < OT_RTTY_ASCII; i++) /* ASCII bits */
        ot_rtty_txbit((c>>i)&1);

    ot_rtty_txbit (1); /* Stop bit */
}

void ot_rtty_txstring (char * string)
{
    /* Simple function to sent a char at a time to 
     * rtty_txbyte function. 
     * NB Each char is one byte (8 Bits)
     */

    char c;

    c = *string++;

    while ( c != '\0')
    {
        ot_rtty_txbyte (c);
        c = *string++;
    }
}

void ot_rtty_send_temperature(float t)
{
	int temp;
	char buf[4];

	/* negative? */
	if (t<0)
		ot_rtty_txbyte('-');

	/* integer part */	
	temp = (int)t;

	itoa(temp, buf, 10);
	ot_rtty_txstring(buf);
	ot_rtty_txbyte('.');

	/* decimal part */
	temp = (t - temp) * 100;
	itoa(temp, buf, 10);
	ot_rtty_txstring(buf);

	ot_rtty_txstring(" C");
}

void ot_rtty_send_pressure(long p)
{
	int temp;
	char buf[5];
	float t;

	t=p/100.0; /* to hPa */

	/* negative? */
	if (p<0)
		ot_rtty_txbyte('-');

	/* integer part */	
	temp = (int)t;

	itoa(temp, buf, 10);
	ot_rtty_txstring(buf);
	ot_rtty_txbyte('.');

	/* decimal part */
	temp = (t - temp) * 100;
	itoa(temp, buf, 10);
	ot_rtty_txstring(buf);

	ot_rtty_txstring(" hPa");

}
