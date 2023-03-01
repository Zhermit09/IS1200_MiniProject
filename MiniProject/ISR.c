#include "pic32mx.h"
#include <stdint.h>
#include "io.h"

extern int delayAmount;
extern int64_t timer;

void checkBts() {
	if ((getBtns() & 8) == 0) {
		button4 = 1;
	}
	if ((getBtns() & 4) == 0) {

		button3 = 1;

	}
	if ((getBtns() & 2) == 0) {
		button2 = 1;
	}

	if ((getBtns() & 2) == 0) {
		button1 = 1;
	}
}

void ISR() {

	if (IFS(0) & 0x100) {

		checkBts();

		if (delayAmount > 0) {
			delayAmount--;
		}

		timer++;
		//PORTE = getBtns();

		IFSCLR(0) = 0x100;
	}
}

