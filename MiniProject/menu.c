#include "pic32mx.h"
#include "io.h"
#include "menu.h"
#include "game.h"

#define sWidth(x) fontz[(int)(x - 32)].width

extern gameON;
extern int seed;


void highscore() {
	ClearDisplay;
	printText("Highscore", pos(51, 1), scale(1, 1));
	printText(hScores[0].initials, pos(57, 7), scale(1, 1));
	printText(hScores[1].initials, pos(57, 14), scale(1, 1));
	printText(hScores[2].initials, pos(57, 21), scale(1, 1));
	Iprint(hScores[0].score, pos(77, 12), scale(1, 1));
	Iprint(hScores[0].score, pos(77, 19), scale(1, 1));
	Iprint(hScores[0].score, pos(77, 26), scale(1, 1));
	displayUpdate();
	while (1) {                     // Retur alternativ till menu (1 knapp)
		if ((getBtns() & 1) == 1) {
			break;
		}
	}
}
void controls() {
	ClearDisplay;
	printText("Controls", pos(52, 3), scale(1, 1));
	printText("Button 1: ESC", pos(1, 9), scale(1, 1));
	printText("Button 2: Select", pos(1, 15), scale(1, 1));
	printText("Button 3: Down/Dash", pos(1, 21), scale(1, 1));
	printText("Button 4: Up/Jump", pos(1, 27), scale(1, 1));
	displayUpdate();

	while (1) {                     // Retur alternativ till menu (1 knapp)
		if ((getBtns() & 1) == 1) {
			break;
		}
	}
	// Bestämd utskrift
}

void credits() {

	ClearDisplay;
	printText("Credits", pos(54, 3), scale(1, 1));
	printText("Pavel Urvantsev (20030502-8615)", pos(1, 9), scale(1, 1));
	printText("Mehrdad Vafaee (20020915-8211)", pos(1, 15), scale(1, 1));
	displayUpdate();

	while (1) {                     // Retur alternativ till menu (1 knapp)
		if ((getBtns() & 1) == 1) {
			break;
		}
	}
	// Bestämd utskrift
}

void printMenu(int menuOption) {
	ClearDisplay;
	switch (menuOption) {
	case 1:
		printText("-> Play", pos(47, 5), scale(1, 1));
		printText("Highscore", pos(51, 12), scale(1, 1));
		printText("Controls", pos(52, 19), scale(1, 1));
		printText("Credits", pos(54, 26), scale(1, 1));
		break;
	case 2:
		printText("Play", pos(58, 5), scale(1, 1));
		printText("-> Highscore", pos(40, 12), scale(1, 1));
		printText("Controls", pos(52, 19), scale(1, 1));
		printText("Credits", pos(54, 26), scale(1, 1));
		break;
	case 3:
		printText("Play", pos(58, 5), scale(1, 1));
		printText("Highscore", pos(51, 12), scale(1, 1));
		printText("-> Controls", pos(41, 19), scale(1, 1));
		printText("Credits", pos(54, 26), scale(1, 1));
		break;
	case 4:
		printText("Play", pos(58, 5), scale(1, 1));
		printText("Highscore", pos(51, 12), scale(1, 1));
		printText("Controls", pos(52, 19), scale(1, 1));
		printText("-> Credits", pos(43, 26), scale(1, 1));
		break;
	default:
		break;
	}

	displayUpdate();
}

void genSeed() {
	int i;
	seed = (int)(stopTimer() * 1000000000);
	for (i = 0; i < 10; i++) {
		srand(seed);
		seed = rand();
	}
}

void menu() {
	int menuOption = 1;
	int exitMenu = 0;

	//void printText(char* string, struct vec pos, struct vec scale, enum Align align, enum Border border, enum Invert invert);
	printMenu(menuOption);
	while (!exitMenu) {
		PORTE = T_PERIOD_VALUE;
		if ((getBtns() & 8) == 8) {
			menuOption--;
			if (menuOption < 1)
			{
				menuOption = 4;
			}
			printMenu(menuOption);
		}
		if ((getBtns() & 4) == 4) {
			menuOption++;
			if (menuOption > 4)
			{
				menuOption = 1;
			}

			printMenu(menuOption);

		}
		if ((getBtns() & 2) == 2) {

			switch (menuOption) {
			case 1:
				gameON = 1;
				exitMenu = 1;
				genSeed();
				break;
			case 2:
				highscore();
				break;
			case 3:
				controls();
				break;
			case 4:
				credits();
				break;
			default:
				break;
			}
			printMenu(menuOption);
		}
	}
	// Bestämd utskrift 
	// Stäng av alternativ?? 
}

void printGameOver(int gameOverOption) {

	ClearDisplay;

	switch (gameOverOption) {
	case 1:
		printText("GAME OVER", pos(47, 10), scale(1, 1));
		printText("-> Retry", pos(28, 20), scale(1, 1));
		printText("Menu", pos(74, 20), scale(1, 1));
		break;
	case 2:
		printText("GAME OVER", pos(47, 10), scale(1, 1));
		printText("Retry", pos(32, 20), scale(1, 1));
		printText("-> Menu", pos(63, 20), scale(1, 1));
		break;
	default:
		break;
	}
	displayUpdate();
}

void gameOver() {
	int gameOverOption = 1;
	int exitGameOver = 0;

	printGameOver(gameOverOption);

	while (!exitGameOver) {
		ClearDisplay;

		if ((getBtns() & 8) == 8) {   // Gå upp och ner i menyn med knappar (2 knappar)

			gameOverOption--;
			if (gameOverOption < 1)
			{
				gameOverOption = 2;
			}

			printGameOver(gameOverOption);

		}
		if ((getBtns() & 4) == 4) {   // Gå upp och ner i menyn med knappar (2 knappar)

			gameOverOption++;
			if (gameOverOption > 2)
			{
				gameOverOption = 1;
			}

			printGameOver(gameOverOption);

		}
		if ((getBtns() & 2) == 2) { // Select knapp som går in i vald alternativ (1 knapp)
			switch (gameOverOption) {
			case 1:
				gameON = 1;
				break;
			case 2:
				break;
			default:
				break;
			}
			exitGameOver = 1;
			delay(1000);
		}
	}
}


int hsMenuOption = 0;
char myInitials[3] = "AAA";

void printInitials(struct Vec p) {
	struct Vec a = pos(p.x, p.y + 6);

	printText(myInitials, p, scale(1, 1));

	switch (hsMenuOption) {
	case 0:
		a.x = p.x + (sWidth(myInitials[0]) - 5) / 2;
		break;
	case 1:
		a.x = p.x + 1 + sWidth(myInitials[0]) + (sWidth(myInitials[1]) - 5) / 2;
		break;
	case 2:
		a.x = p.x + 2 + sWidth(myInitials[0]) + sWidth(myInitials[1]) + (sWidth(myInitials[2]) - 5) / 2;
		break;
	default:
		break;
	}
	printText("^", a, scale(1, 1));
	displayUpdate();
}

//int updating = 1;
void highscoreUpdate(int count) {
	struct Vec p = pos(47, 10);

	int i;
	int j;

	for (i = 2; i > count; i--)
	{
		for (j = 0; j < 3; j++) {
			hScores[i].initials[j] = hScores[i-1].initials[j];
		}
	}
	ClearDisplay;
	printInitials(p);

	while (1)
	{
		ClearDisplay;
		delay(100);

		if ((getBtns() & 8) == 8) {
			hsMenuOption++;
			if (hsMenuOption > 2)
			{
				hsMenuOption = 0;
			}
			printInitials(p);
		}
		if ((getBtns() & 4) == 4) {
			myInitials[hsMenuOption]++;

			if (myInitials[hsMenuOption] > 90)
			{
				myInitials[hsMenuOption] = 65;
			}

			printInitials(p);
		}
		if ((getBtns() & 2) == 2) {
			hsMenuOption = 0;
			myInitials[0] = 'A';
			myInitials[1] = 'A';
			myInitials[2] = 'A';
			delay(1000);
			break;
		}
	}

}

void scoreCheck(int score) {
	if (score > hScores[0].score)
	{
		hScores[2].score = hScores[1].score;
		hScores[1].score = hScores[0].score;
		hScores[0].score = score;
		highscoreUpdate(0);
	}
	else if (score > hScores[1].score)
	{
		hScores[2].score = hScores[1].score;
		hScores[1].score = score;
		highscoreUpdate(1);
	}
	else if (score > hScores[2].score)
	{
		hScores[2].score = score;
		highscoreUpdate(2);
	}
}
