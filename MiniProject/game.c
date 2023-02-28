#include "game.h"
#include "menu.h"
#define bHeight 4
#define bWidth 4
#define pos(x,y) (struct Vec){x,y}
#define scale(x,y) (struct Vec){x,y}

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
	printNum((float)rand(), pos(50, 10), scale(1, 1));

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