#include "game.h"
#include "menu.h"
#define bHeight 4
#define bWidth 6
#define pHeight 31
#define pWidth 9
#define GAP 16
#define SPACE 23

extern gameON;
const float g = 9.82f;

int seed = 0;

double dt = 0;
double time = 0;
int c = 0;
float fps = 0;


struct HighScore hScores[3];

uint8_t birdMatrix[bHeight][bWidth] =
{
	{1,1,1,_,_,_},
	{_,1,_,1,1,_},
	{_,1,1,1,1,1},
	{1,1,1,1,_,_}
};

uint8_t pipeMatrix[pHeight][pWidth] =
{
	{1,1,1,1,1,1,1,1,1},
	{1,_,_,_,_,_,_,_,1},
	{1,1,1,1,1,1,1,1,1},
	{_,1,1,1,_,1,_,1,_},
	{_,1,1,_,1,_,_,1,_},
	{_,1,1,1,_,1,_,1,_},
	{_,1,1,_,1,_,_,1,_},
	{_,1,1,1,_,1,_,1,_},
	{_,1,1,_,1,_,_,1,_},
	{_,1,1,1,_,1,_,1,_},
	{_,1,1,_,1,_,_,1,_},
	{_,1,1,1,_,1,_,1,_},
	{_,1,1,_,1,_,_,1,_},
	{_,1,1,1,_,1,_,1,_},
	{_,1,1,_,1,_,_,1,_},
	{_,1,1,1,_,1,_,1,_},
	{_,1,1,_,1,_,_,1,_},
	{_,1,1,1,_,1,_,1,_},
	{_,1,1,_,1,_,_,1,_},
	{_,1,1,1,_,1,_,1,_},
	{_,1,1,_,1,_,_,1,_},
	{_,1,1,1,_,1,_,1,_},
	{_,1,1,_,1,_,_,1,_},
	{_,1,1,1,_,1,_,1,_},
	{_,1,1,_,1,_,_,1,_},
	{_,1,1,1,_,1,_,1,_},
	{_,1,1,_,1,_,_,1,_},
	{_,1,1,1,_,1,_,1,_},
	{1,1,1,1,1,1,1,1,1},
	{1,_,_,_,_,_,_,_,1},
	{1,1,1,1,1,1,1,1,1},
};

struct Sprite pImage;

void gameSetup() {

	bird.image = (struct Sprite){ bHeight, bWidth, &birdMatrix[0][0] };
	bird.pos = pos(10, 10);

	bird.hit = 0;
	bird.y_vel = 0;
	int i;
	int x = 0;
	pImage = (struct Sprite){ pHeight, pWidth, &pipeMatrix[0][0] };

	hScores[0] = (struct HighScore){ "___", 0 };
	hScores[1] = (struct HighScore){ "___", 0 };
	hScores[2] = (struct HighScore){ "___", 0 };


}

int matrixOverlap(struct Vec pos1, struct Vec size1, struct Vec pos2, struct Vec size2) {
	if ((pos1.x < pos2.x + size2.x) && (pos2.x < pos1.x + size1.x) && (pos1.y < pos2.y + size2.y) && (pos2.y < pos1.y + size1.y)) {
		return 1;
	}
	return 0;
}

void jump() {
	if (bird.pos.y > 25) {
		bird.y_vel = -650 * dt;
	}

}

void dash() {

	if (bird.pos.x == 10) {
		bird.x_vel = 2300 * dt;
		bird.y_vel = 0;
	}
}

void glide() {

	int s = bird.x_vel * 10 * dt;
	bird.x_vel -= (g / 2) / 20 * 275 * dt;

	if (s > 4) {
		s = 4;
	}

	bird.pos.x += (int)(s + 0.5);


	if (bird.pos.x < 10) {
		bird.pos.x = 10;
	}


}

void gravity() {
	int s = bird.y_vel * 50 * dt;
	bird.y_vel += (g / 2) / 20 * 100 * dt;

	if (s > 4) {
		s = 4;
	}

	bird.pos.y += (int)(s + 0.5);

}

void movePipe(struct Pipe pipe) {
	pipe.pos.x -= 30;
}

void UI() {
	if (time > 1) {
		fps = c / (time);
		time = 0;
		c = 0;
	}
	Fprint(fps, pos(110, 1), scale(1, 1));
	c++;
	time += dt;

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
	int i;

	for (i = 0; i < 4; i++) {
		pipes[i].pos = pos((10 + i * (pWidth + SPACE)), rand() % (28- (GAP + 4)) + GAP + 4);
	}

	startTimer();
	while (gameON) {
		dt = stopTimer();
		startTimer();

		ClearDisplay;

		for(i = 0; i<4;i++){
		drawSprite(pImage, pipes[i].pos, scale(1, 1));
		drawSprite(pImage, pos(pipes[i].pos.x, pipes[i].pos.y - pHeight - GAP), scale(1, 1));
		}
		drawSprite(bird.image, bird.pos, scale(1, 1));
		UI();
		displayUpdate();

		gravity();
		glide();
		jump();

		if ((getBtns() & 8) == 8) {
		}
		if ((getBtns() & 4) == 4) {
			dash();
		}
		if ((getBtns() & 2) == 2) {
			bird.y_vel = -500 * dt;
		}
		if ((getBtns() & 1) == 1) {
			gameON = 0;
		}
	}
}

