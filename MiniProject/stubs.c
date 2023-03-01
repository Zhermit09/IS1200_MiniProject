#include "pic32mx.h"
#include "io.h"

extern void enable_interrupts(void);// {};

void initLed() {
	TRISECLR = 0xff;					//Led out
	PORTE = 0;
}

void initHID() {
	TRISDSET = 0x7f << 5;				//Switch and buttons 4-2 in
	TRISFSET = 0x2;						//button 1


}

void initTimer() {
	T2CON = 0;							//Timer
	TMR2 = 0;							//counter
	PR2 = T_PERIOD_VALUE;				//period
	IFSCLR(0) = 0x100;					//flag

	IPCCLR(2) = 0x1f;					//(sub)priorities
	IPCSET(2) = 0x1f;
	IECSET(0) = 0x100;					//Enable interruputs

	T2CON = 0x8000 | T_PRESCALE_VALUE;	//Start timer / prescale
}

void preDisplayInit() {
	//Set up peripheral bus clock
	OSCCONCLR = 0x180000;				//Peripheral bus clock scaling Max 10Mhz
	OSCCONSET = 0x080000;				//1:1, 1:2, 1:4, 1:8	sysclk ti pbclk (bits 20-19)

	//Set up output pins
	AD1PCFG = 0xFFFF;
	ODCE = 0x0;

	//Output pins for display signals
	ODCF = 0x0;
	ODCG = 0x0;

	//Display output control pins
	TRISFCLR = 7 << 4;
	TRISGCLR = 1 << 9;

	//Display intput pins?
	TRISDSET = 1 << 8;

	//Set up SPI as master
	SPI2CON = 0;
	SPI2BRG = 1 << 2;

	SPI2STATCLR = 1 << 6;				//Clear SPIROV
	SPI2CONSET = 0x8060;				//Turn on SPI, Set CKP = 1, MSTEN = 1
}

/* Non-Maskable Interrupt; something bad likely happened, so hang */
void _nmi_handler() {
	for(;;);
}

/* This function is called upon reset, before .data and .bss is set up */
void _on_reset() {
	
}

/* This function is called before main() is called, you can do setup here */
void _on_bootstrap() {
	
	button4 = 0;
	button3 = 0;
	button2 = 0;
	button1 = 0;

	initLed();
	initHID();
	initTimer();
	
	enable_interrupts();
	preDisplayInit();
}
