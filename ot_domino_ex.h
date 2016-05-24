#include <inttypes.h>
#include "msp430.h"
#include "ot_radio.h"

#ifndef _OT_DOMINOEX_H
#define _OT_DOMINOEX_H

void ot_dominoex_txsym(uin8_t sym);
void ot_dominoex_txchar(uint16_t vcode);
void ot_dominoex_txstring(char* s);
void ot_dominoex_txid(char* s);

#endif
