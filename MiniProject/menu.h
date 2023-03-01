#ifndef _MENU_
#define _MENU_
#include "io.h"

#define bt4 ((getBtns() & 8) == 8) && button4
#define bt3 ((getBtns() & 4) == 4) && button3
#define bt2 ((getBtns() & 2) == 2) && button2
#define bt1 ((getBtns() & 1) == 1) && button1

struct HighScore {
	char initials[3];
	int score;
};

extern struct HighScore hScores[];

void menu();
void highscore();
void credits();
void controls();
void gameOver();
#endif