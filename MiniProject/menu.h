#ifndef _MENU_
#define _MENU_

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