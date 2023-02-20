#ifndef _IO_
#define _IO_

#include "pic32mx.h"

//Value must be in the (0, 0.2] seconds range
#define	T_PERIOD 0.1

//256, 64, 32, 16, 8, 4, 2, 1 Only
#define T_PRESCALE 256
#define T_PERIOD_VALUE (T_PERIOD * 80000000 / T_PRESCALE)

#ifdef T_PRESCALE
#if T_PRESCALE == 256
#define T_PRESCALE_VALUE (7<<4);
#elif T_PRESCALE == 64
#define T_PRESCALE_VALUE (6<<4);
#elif T_PRESCALE == 32
#define T_PRESCALE_VALUE (5<<4);
#elif T_PRESCALE == 16
#define T_PRESCALE_VALUE (4<<4);
#elif T_PRESCALE == 8
#define T_PRESCALE_VALUE (3<<4);
#elif T_PRESCALE == 4
#define T_PRESCALE_VALUE (2<<4);
#elif T_PRESCALE == 2
#define T_PRESCALE_VALUE (1<<4);
#elif T_PRESCALE == 1
#define T_PRESCALE_VALUE 0;
#endif
#endif

void delay(int ms);
int getSw(void);
int getBtns(void);

#endif // end of _IO_