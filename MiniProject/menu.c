#include "pic32mx.h"
#include "io.h"
#include "menu.h"
#include "game.h"


void printMenu(int menuOption) {

	switch (menuOption) {
	case 1:
		printText("Play", pos(1, 5), scale(1, 1), CENTER, BORDER, INVERT);
		printText("Highscore", pos(1, 12), scale(1, 1), CENTER, BORDER, NO_INVERT);
		printText("Controls", pos(1, 19), scale(1, 1), CENTER, BORDER, NO_INVERT);
		printText("Credits", pos(1, 26), scale(1, 1), CENTER, BORDER, NO_INVERT);
		break;
	case 2:
		printText("Play", pos(1, 5), scale(1, 1), CENTER, BORDER, NO_INVERT);
		printText("Highscore", pos(1, 12), scale(1, 1), CENTER, BORDER, INVERT);
		printText("Controls", pos(1, 19), scale(1, 1), CENTER, BORDER, NO_INVERT);
		printText("Credits", pos(1, 26), scale(1, 1), CENTER, BORDER, NO_INVERT);
		break;
	case 3:
		printText("Play", pos(1, 5), scale(1, 1), CENTER, BORDER, NO_INVERT);
		printText("Highscore", pos(1, 12), scale(1, 1), CENTER, BORDER, NO_INVERT);
		printText("Controls", pos(1, 19), scale(1, 1), CENTER, BORDER, INVERT);
		printText("Credits", pos(1, 26), scale(1, 1), CENTER, BORDER, NO_INVERT);
		break;
	case 4:
		printText("Play", pos(1, 5), scale(1, 1), CENTER, BORDER, NO_INVERT);
		printText("Highscore", pos(1, 12), scale(1, 1), CENTER, BORDER, NO_INVERT);
		printText("Controls", pos(1, 19), scale(1, 1), CENTER, BORDER, NO_INVERT);
		printText("Credits", pos(1, 26), scale(1, 1), CENTER, BORDER, INVERT);
		break;
	default:
		break;
	}

	displayUpdate();
}

void highscore() {
	ClearDisplay;
	printText("Highscore", pos(1, 5), scale(1, 1), CENTER, BORDER, NO_INVERT);
	displayUpdate();
	while (1) {                     // Retur alternativ till menu (1 knapp)
		if ((getBtns() & 1) == 1) {
			break;
		}
	}


	// Laddar upp tre senaste highscores
}

void controls() {
	ClearDisplay;
	printText("Controls", pos(1, 5), scale(1, 1), CENTER, BORDER, NO_INVERT);
	printText("Placeholder", pos(1, 12), scale(1, 1), CENTER, BORDER, NO_INVERT);
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
	printText("Credits", pos(1, 5), scale(1, 1), CENTER, BORDER, NO_INVERT);
	printText("Placeholder", pos(1, 12), scale(1, 1), CENTER, NO_BORDER, NO_INVERT);
	displayUpdate();

	while (1) {                     // Retur alternativ till menu (1 knapp)
		if ((getBtns() & 1) == 1) {
			break;
		}
	}
	// Bestämd utskrift
}

void menu() {
	int menuOption = 1;

	ClearDisplay;

	printText("Play", pos(1, 5), scale(1, 1), CENTER, BORDER, INVERT);
	printText("Highscore", pos(1, 12), scale(1, 1), CENTER, BORDER, NO_INVERT);
	printText("Controls", pos(1, 19), scale(1, 1), CENTER, BORDER, NO_INVERT);
	printText("Credits", pos(1, 26), scale(1, 1), CENTER, BORDER, NO_INVERT);
	displayUpdate();
	//void printText(char* string, struct vec pos, struct vec scale, enum Align align, enum Border border, enum Invert invert);

	while (1)
	{
		ClearDisplay;


		PORTE = getBtns();


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

			if (menuOption == 1) {
				game();
			}
			else if (menuOption == 2) {
				highscore();
			}
			else if (menuOption == 3) {
				controls();
			}
			else if (menuOption == 4) {

				credits();
			}

			/*switch (menuOption) {
			case 1:

				break;
			case 2:

				break;
			case 3:

				break;
			case 4:

				break;
			default:
				break;
			}*/
		}
	}

	// Bestämd utskrift 
	// Stäng av alternativ?? 
}

void printGameOver(int gameOverOption) {
	switch (gameOverOption) {
	case 1:
		printText("Retry", pos(32, 20), scale(1, 1), CENTER, BORDER, INVERT);
		printText("Menu", pos(96, 20), scale(1, 1), CENTER, BORDER, NO_INVERT);
		break;
	case 2:
		printText("Retry", pos(32, 20), scale(1, 1), CENTER, BORDER, NO_INVERT);
		printText("Menu", pos(96, 20), scale(1, 1), CENTER, BORDER, INVERT);
		break;
	default:
		break;
	}
	displayUpdate();
}

void gameOver() {
	int gameOverOption = 1;

	ClearDisplay;

	printText("GAME OVER", pos(20, 10), scale(1, 1), CENTER, BORDER, NO_INVERT);
	printText("Retry", pos(32, 20), scale(1, 1), CENTER, BORDER, NO_INVERT);
	printText("Menu", pos(96, 20), scale(1, 1), CENTER, BORDER, NO_INVERT);

	displayUpdate();
	while (1)
	{
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
				//gameReset();
				game();
				break;
			case 2:
				delay(2000);
				menu();
				break;
			default:
				break;
			}
		}
	}
}
