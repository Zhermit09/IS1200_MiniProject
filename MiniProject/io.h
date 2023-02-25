#ifndef _IO_
#define _IO_

#include "pic32mx.h"
#include <stdint.h>

#define _ 0

#define CMD_MODE_ON PORTFCLR = 1 << 4
#define CMD_MODE_OFF PORTFSET = 1 << 4

#define DISPLAY_VDD_ON PORTFCLR = 1 << 6
#define DISPLAY_VDD_OFF PORTFSET = 1 << 6

#define DISPLAY_RESET_ON PORTGCLR = 1 << 9
#define DISPLAY_RESET_OFF PORTGSET = 1 << 9

#define DISPLAY_VBATT_ON PORTFCLR = 1 << 5
#define DISPLAY_VBATT_OFF PORTFSET = 1 << 5

//Value must be in the (0, 0.2] seconds range with 256 prescale
#define	T_PERIOD 0.1

//256, 64, 32, 16, 8, 4, 2, 1 Only
#define T_PRESCALE 256
#define T_PERIOD_VALUE (T_PERIOD * 80000000 / T_PRESCALE)

#ifdef T_PRESCALE
#if T_PRESCALE == 256
#define T_PRESCALE_VALUE (7<<4);
#elif T_PRESCALE == 64
#define T_PRESCALE_VALUE (6<<4);
#elif T_PRESCALE == 32
#define T_PRESCALE_VALUE (5<<4);
#elif T_PRESCALE == 16
#define T_PRESCALE_VALUE (4<<4);
#elif T_PRESCALE == 8
#define T_PRESCALE_VALUE (3<<4);
#elif T_PRESCALE == 4
#define T_PRESCALE_VALUE (2<<4);
#elif T_PRESCALE == 2
#define T_PRESCALE_VALUE (1<<4);
#elif T_PRESCALE == 1
#define T_PRESCALE_VALUE 0;
#endif
#endif

uint8_t canvas[32][128];

typedef struct Vec {
	int x;
	int y;
}vec;

typedef struct Sprite {
	int height;
	int width;
	uint8_t *sprite;
}sprite;

enum Align { NO_ALIGN, LEFT, X_CENTER, Y_CENTER, CENTER, RIGHT };
enum Border { NO_BORDER, BORDER };
enum Invert { NO_INVERT, INVERT };

void delay(int ms);
int getSw(void);
int getBtns(void);

uint8_t spi(uint8_t data);
void displayUpdate();
void printText(char* string, struct Vec pos, struct Vec scale, enum Align align, enum Border border, enum Invert invert);
void drawSprite(struct Sprite asset, struct Vec pos, struct Vec scale);

void fontInit();

#endif // end of _IO_