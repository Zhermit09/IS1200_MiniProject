#include "pic32mx.h"
#include "io.h"
#include <stdint.h>

#define DISPLAY_VDD PORTFbits.RF6
#define DISPLAY_VBATT PORTFbits.RF5
#define DISPLAY_COMMAND_DATA PORTFbits.RF4
#define DISPLAY_RESET PORTGbits.RG9


#define DISPLAY_VDD_PORT PORTF
#define DISPLAY_VDD_MASK 0x40
#define DISPLAY_VBATT_PORT PORTF
#define DISPLAY_VBATT_MASK 0x20
#define DISPLAY_COMMAND_DATA_PORT PORTF
#define DISPLAY_COMMAND_DATA_MASK 0x10
#define DISPLAY_RESET_PORT PORTG
#define DISPLAY_RESET_MASK 0x200

char textBuffer[4][16];		//Ska vara global eller n�t


uint8_t spi_send_recv(uint8_t data) {
	while (!(SPI2STAT & 0x08));
	SPI2BUF = data;
	while (!(SPI2STAT & 0x01));
	return SPI2BUF;
}

void oledUpdate() {
	int i,j,k;
	int c;

	
	for (i = 0; i < 4; i++) {
		PORTF &= ~0x10;

		spi_send_recv(0x22);
		spi_send_recv(i);

		spi_send_recv(0x00);
		spi_send_recv(0x10);

		PORTF |= 0x10;


		for (j = 0; j < 16; j++) {
			c = textBuffer[i][j];
			if (c & 0x80) {
				continue;
			}
			for (k = 0; k < 8;k++) {
				spi_send_recv(255);
			}
		}
	}

}

int main() {
	/* Set up peripheral bus clock */
	OSCCON &= ~0x180000;
	OSCCON |= 0x080000;

	/* Set up output pins */
	AD1PCFG = 0xFFFF;
	ODCE = 0x0;
	TRISECLR = 0xFF;
	PORTE = 0x0;

	/* Output pins for display signals */
	PORTF = 0xFFFF;
	PORTG = (1 << 9);
	ODCF = 0x0;
	ODCG = 0x0;
	TRISFCLR = 0x70;
	TRISGCLR = 0x200;

	/* Set up input pins */
	TRISDSET = (1 << 8);
	TRISFSET = (1 << 1);

	/* Set up SPI as master */
	SPI2CON = 0;
	SPI2BRG = 4;

	/* Clear SPIROV*/
	SPI2STATCLR &= ~0x40;
	/* Set CKP = 1, MSTEN = 1; */
	SPI2CON |= 0x60;

	/* Turn on SPI */
	SPI2CONSET = 0x8000;

//---------------------------

	DISPLAY_COMMAND_DATA_PORT &= ~DISPLAY_COMMAND_DATA_MASK;
	delay(1);
	DISPLAY_VDD_PORT &= ~DISPLAY_VDD_MASK;
	delay(100);

	spi_send_recv(0xAE);
	DISPLAY_RESET_PORT &= ~DISPLAY_RESET_MASK;
	delay(1);
	DISPLAY_RESET_PORT |= DISPLAY_RESET_MASK;
	delay(1);

	spi_send_recv(0x8D);
	spi_send_recv(0x14);

	spi_send_recv(0xD9);
	spi_send_recv(0xF1);

	DISPLAY_VBATT_PORT &= ~DISPLAY_VBATT_MASK;
	delay(100);

	spi_send_recv(0xA1);
	spi_send_recv(0xC8);

	spi_send_recv(0xDA);
	spi_send_recv(0x20);

	spi_send_recv(0xAF);

	oledUpdate();
	while (1) {
		PORTE = ~PORTE;
		delay(100);
	}
	return 0;
}
