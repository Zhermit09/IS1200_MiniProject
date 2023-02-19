#include "pic32mx.h"

int i = 0;

void ISR() {

	if (IFS(0) & 0x100) {

		if (i == 10) {
			PORTE = ~PORTE;
			i = 0;
		}
		i++;
		IFSCLR(0) = 0x100;
	}
}
