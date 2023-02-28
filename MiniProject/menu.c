#include "pic32mx.h"
#include "io.h"
#include "menu.h"
#include "game.h"

extern gameON;


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

void highscore() {
	ClearDisplay;
	printText("Highscore", pos(51, 3), scale(1, 1));
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

void menu() {
	int menuOption = 1;
	int exitMenu = 0;
	
	//void printText(char* string, struct vec pos, struct vec scale, enum Align align, enum Border border, enum Invert invert);
	printMenu(menuOption);
	while (!exitMenu) {

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
