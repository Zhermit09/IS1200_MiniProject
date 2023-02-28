#include "pic32mx.h"
#include <stdint.h>

extern int delayAmount;
extern int64_t timer;

void ISR() {

	if (IFS(0) & 0x100) {

		//PORTE =timer;

		if (delayAmount > 0) {
			delayAmount--;
		}

		timer++;

		IFSCLR(0) = 0x100;
	}
}
