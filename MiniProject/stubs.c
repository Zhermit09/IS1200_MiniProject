#include "pic32mx.h"
#include "io.h"

extern void enable_interrupts(void);//{};

void initLed() {
	TRISECLR = 0xff;						//Led out
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

/* Non-Maskable Interrupt; something bad likely happened, so hang */
void _nmi_handler() {
	for(;;);
}

/* This function is called upon reset, before .data and .bss is set up */
void _on_reset() {
	
}

/* This function is called before main() is called, you can do setup here */
void _on_bootstrap() {
	
	initLed();
	initHID();
	initTimer();
	
	enable_interrupts();
}
