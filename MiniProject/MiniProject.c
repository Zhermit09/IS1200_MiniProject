#include "pic32mx.h"
#include "io.h"
//#include <stdio.h>


void displayInit() {
	CMD_MODE_ON;
	DISPLAY_VDD_ON;						//Power on controller
	delay(1);

	spi(0xAE);							//Display off (sleep)
	DISPLAY_RESET_ON;					//Reset controller
	delay(1);
	DISPLAY_RESET_OFF;

	//Charge pump + pre-charge period commands
	spi(0x8D);
	spi(0x14);

	spi(0xD9);
	spi(0xF1);

	DISPLAY_VBATT_ON;					//Power on display
	delay(100);

	//Inert display cord system
	spi(0xA1);							//remap columns
	spi(0xC8);							//remap rows

	//Sequential COM, non-interleaved display memory
	spi(0xDA);							//COM config
	spi(0x20);							//Sequential COM

	spi(0xAF);							//Display on
}

int main() {
	displayInit();
	fontInit();

	PORTE = 1;
		
	while (1) {

		displayUpdate();

	}
	return 0;
}

//delay(100);
//PORTE = (PORTE & ~0xff) | (getBtns() << 4) | getSw();


//	spi(0x81);							//Contrast
//	spi(a);

/*if (((getBtns() & 8) == 8) && a > 0) {
	a--;
	delay(30);
}
else if (((getBtns() & 4) == 4) && a < 255) {
	a++;
	delay(30);
}*/

//matrixToBuffer(matrix);
//printf("%d", displayBuffer[1][0]);
