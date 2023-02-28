#include "game.h"
#include "menu.h"
#define bHeight 4
#define bWidth 4
#define pos(x,y) (struct Vec){x,y}
#define scale(x,y) (struct Vec){x,y}
#define sWidth(x) fontz[(int)(x - 32)].width

extern gameON;
const float g = 9.82f;
float dt = 0;
int c = 0;

uint8_t birdMatrix[bHeight][bWidth] =
{
	{1,1,1,1},
	{1,1,1,1},
	{1,1,1,1},
	{1,1,1,1}
};

void gameSetup() {

	bird.image = (struct Sprite){ bHeight, bWidth, &birdMatrix[0][0] };
	bird.pos = pos(10, 10);

	bird.hit = 0;
	bird.vel = 0;

	dt = stopTimer();
	srand(10);
}

int matrixOverlap(struct Vec pos1, struct Vec size1, struct Vec pos2, struct Vec size2) {
	if ((pos1.x < pos2.x + size2.x) && (pos2.x < pos1.x + size1.x) && (pos1.y < pos2.y + size2.y) && (pos2.y < pos1.y + size1.y)) {
		return 1;
	}
	return 0;
}

void jump() {
	if (bird.pos.y > 25) {
		bird.vel = -5;
	}

}

void dash() {

}

void gravity() {
	int s = bird.vel;
	bird.vel += (g / 2) / 20;

	if (s > 4) {
		s = 4;
	}

	bird.pos.y += (int)(s + 0.5);

}

void movePipe(struct Pipe pipe) {
	pipe.pos.x -= 30;
}

void UI() {
	Fprint((float)rand(), pos(50, 10), scale(1, 1));

	/*printText(" !\"#$%&\'()*+,-./0123456789:;<=>?", pos, scale, NO_ALIGN, NO_BORDER, NO_INVERT);
	pos.y += 6;
	printText("@ABCDEFGHIJKLMNOP", pos, scale, NO_ALIGN, NO_BORDER, NO_INVERT);
	pos.y += 6;
	printText("QRSTUVWXYZ[\\]^_`", pos, scale, NO_ALIGN, NO_BORDER, NO_INVERT);
	pos.y += 6;
	printText("abcdefghijklmnopqrstuvwxyz{|}~", pos, scale, NO_ALIGN, NO_BORDER, NO_INVERT);
	pos.y += 6;
	printText(" !\"#$%&\'()*+,-./0123456789:;<=>?", pos, scale, NO_ALIGN, NO_BORDER, NO_INVERT);*/
}



void game() {

	while (gameON) {
		dt = stopTimer();
		startTimer();

		ClearDisplay;
		UI();
		drawSprite(bird.image, bird.pos, scale(1, 1));
		displayUpdate();

		gravity();
		jump();

		if ((getBtns() & 8) == 8) {
			bird.pos.x -= 1;
		}
		if ((getBtns() & 4) == 4) {
			bird.pos.x += 1;
		}
		if ((getBtns() & 2) == 2) {
			//bird.pos.y -= 1;
			bird.vel = -3;
		}
		if ((getBtns() & 1) == 1) {
			gameON = 0;
		}
	}

}

extern char initials[4][3];
extern int highscores[3];
int hsMenuOption = 0;

void highscoreUpdate(int count) {
	int i;
	int j;

	for (i = 2; i > count; i--)
	{
		for (j = 0; j < 3; j++) {
			initials[i][j] = initials[i - 1][j];
		}
	}

	ClearDisplay;
	struct Vec p = pos(47, 10);
	printText(initials[3], p, scale(1, 1));

	/*for (i = 0; i < 3; i++) {
		printText(initials[3][i], p, scale(1, 1));
		p.x += fontz[(int)(initials[3][i] - 32)].width+1;

	}*/
	displayUpdate();

	int updating = 1;

	while (updating)
	{
		ClearDisplay;
		delay(100);

		if ((getBtns() & 8) == 8) {
			hsMenuOption++;
			if (hsMenuOption > 2)
			{
				hsMenuOption = 0;
			}
			printText(initials[3], p, scale(1, 1));
			switch (hsMenuOption) {
			case 0:
				printText("^", pos(p.x - (5 - sWidth(initials[3][0]))/2, p.y + 6), scale(1, 1));
				break;
			case 1:
				printText("^", pos(p.x + 1 + sWidth(initials[3][0]) - (5 - sWidth(initials[3][1]))/2, p.y + 6), scale(1, 1));
				break;
			case 2:
				printText("^", pos(p.x + 2 + sWidth(initials[3][0]) + sWidth(initials[3][1]) - (5 - sWidth(initials[3][2]))/2, p.y + 6), scale(1, 1));
				break;
			default:
				break;
			}
			displayUpdate();
		}
		if ((getBtns() & 4) == 4) {
			initials[3][hsMenuOption]++;

			if (initials[3][hsMenuOption] > 90)
			{
				initials[3][hsMenuOption] = 65;
			}

			printText(initials[3], p, scale(1, 1));

			switch (hsMenuOption) {
			case 0:
				printText("^", pos(p.x - (5 - sWidth(initials[3][0])), p.y + 6), scale(1, 1));
				break;
			case 1:
				printText("^", pos(p.x + sWidth(initials[3][0]) - (5 - sWidth(initials[3][1])), p.y + 6), scale(1, 1));
				break;
			case 2:
				printText("^", pos(p.x + sWidth(initials[3][0]) + sWidth(initials[3][1]) - (5 - sWidth(initials[3][2])), p.y + 6), scale(1, 1));
				break;
			default:
				break;
			}
			/*for (i = 0; i < 3; i++) {
				p.x += fontz[(int)(initials[3][i] - 32)].width + 1;

			}*/
			displayUpdate();
		}
		if ((getBtns() & 2) == 2) {
			updating = 0;
		}
	}

}

void scoreCheck(int score) {
	if (score > highscores[0])
	{
		highscores[2] = highscores[1];
		highscores[1] = highscores[0];
		highscores[0] = score;
		highscoreUpdate(0);
	}
	else if (score > highscores[1])
	{
		highscores[2] = highscores[1];
		highscores[1] = score;
		highscoreUpdate(1);
	}
	else if (score > highscores[2])
	{
		highscores[2] = score;
		highscoreUpdate(2);
	}
}