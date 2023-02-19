#pragma once
#include "pic32mx.h"

int getsw(void) {

	return ((PORTD >> 8) & 0xf);
}

int getbtns(void) {
	return (((PORTD >> 4) & 0xe) | ((PORTF >> 1) & 0x1));	//Button 4-2 + 1
}

//Debug LEDs
//PORTE = (PORTE & ~0xff) | (getbtns() << 4) | getsw();

/*
if (IFS(0) & 0x100) {
	PORTE = ~PORTE;
	IFSCLR(0) = 0x100;
}*/