#include "pic32mx.h"

extern int delayAmount;
int i = 0;

void ISR() {

	if (IFS(0) & 0x100) {

		//PORTE = ~PORTE;

		if (delayAmount > 0) {
			delayAmount--;
		}

		IFSCLR(0) = 0x100;
	}
}
