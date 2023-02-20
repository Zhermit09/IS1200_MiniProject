#include "pic32mx.h"
#include "io.h"

int delayAmount = 0;

void delay(int ms) {

	delayAmount = ms / (1000 * T_PERIOD);

	while (delayAmount > 0)
	{//Wait
	}
}

int getSw(void) {

	return ((PORTD >> 8) & 0xf);
}

int getBtns(void) {
	return (((PORTD >> 4) & 0xe) | ((PORTF >> 1) & 0x1));	//Button 4-2 + 1
}

//Debug LEDs
//PORTE = (PORTE & ~0xff) | (getbtns() << 4) | getsw();

/*
if (IFS(0) & 0x100) {
	PORTE = ~PORTE;
	IFSCLR(0) = 0x100;
}*/
