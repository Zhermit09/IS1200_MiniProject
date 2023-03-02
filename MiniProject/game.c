#include "game.h"
#include "menu.h"
#define bHeight 4
#define bWidth 6
#define pHeight 31
#define pWidth 9
#define SPACE 23
#define round(x) (int)(x+0.5)

extern gameON;
const float g = 9.82f;

int seed = 0;
int score = 0;
int oldScore = 0;

double dt = 0;
double time = 0;
int c = 0;
float fps = 0;

int GAP = 23;
double PSPEED = 20.0;

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

uint8_t groundMatrix[2][128] =
{
	{_,1,_,1,_,1,_,1,_,1,_,1,_,1,_,1,_,1,_,1,_,1,_,1,_,1,_,1,_,1,_,1,_,1,_,1,_,1,_,1,_,1,_,1,_,1,_,1,_,1,_,1,_,1,_,1,_,1,_,1,_,1,_,1,_,1,_,1,_,1,_,1,_,1,_,1,_,1,_,1,_,1,_,1,_,1,_,1,_,1,_,1,_,1,_,1,_,1,_,1,_,1,_,1,_,1,_,1,_,1,_,1,_,1,_,1,_,1,_,1,_,1,_,1,_,1,_,1},
	{1,_,1,_,1,_,1,_,1,_,1,_,1,_,1,_,1,_,1,_,1,_,1,_,1,_,1,_,1,_,1,_,1,_,1,_,1,_,1,_,1,_,1,_,1,_,1,_,1,_,1,_,1,_,1,_,1,_,1,_,1,_,1,_,1,_,1,_,1,_,1,_,1,_,1,_,1,_,1,_,1,_,1,_,1,_,1,_,1,_,1,_,1,_,1,_,1,_,1,_,1,_,1,_,1,_,1,_,1,_,1,_,1,_,1,_,1,_,1,_,1,_,1,_,1,_,1,_}
};

void gameSetup() {
	bird.image = (struct Sprite){ bHeight, bWidth, &birdMatrix[0][0] };
	bird.x = 10;
	bird.y = 5;

	bird.hit = 0;
	bird.y_vel = 0;
	int i;
	int x = 0;
	pImage = (struct Sprite){ pHeight, pWidth, &pipeMatrix[0][0] };
	gImage = (struct Sprite){ 3, 128, &groundMatrix[0][0] };

	hScores[0] = (struct HighScore){ "___", 0 };
	hScores[1] = (struct HighScore){ "___", 0 };
	hScores[2] = (struct HighScore){ "___", 0 };

	ground[0] = (struct Ground){ 0,30 };
	ground[1] = (struct Ground){ 127,30 };

	for (i = 0; i < 5; i++) {
		pipes[i].x = 128 + i * (pWidth + SPACE);
		pipes[i].y = rand() % (28 - (GAP + 4)) + GAP + 4;
	}
}

void dash() {

	if (bird.x == 10) {
		bird.x_vel = (300 * dt);
		bird.y_vel = -50 * dt;
	}
}

void glide() {

	double s = 0.5 * bird.x_vel * 60 * dt;
	bird.x_vel -= g * 1.5 * dt;

	if (s > 1.5) {
		s = 1.5;
	}
	if (s < -PSPEED * dt) {
		s = -PSPEED * dt;
	}

	bird.x += s;


	if (bird.x < 10) {
		bird.x = 10;
	}
}

void jump() {
	bird.y_vel = -(230.0 * dt);
}

void gravity() {
	double s = 0.5 * bird.y_vel * 40 * dt;
	bird.y_vel += g * 1.07 * dt;

	if (s > 1.5) {
		s = 1.5;
	}

	bird.y += s;

}

void UI() {
	if (time > 1) {
		fps = c / (time);
		time = 0;
		c = 0;
	}
	Fprint(fps, pos(110, 1));
	Iprint(score, pos(61, 7));
	c++;
	time += dt;
}

void pipeCycle(int i) {
	if (pipes[i].x <= -pWidth) {
		pipes[i].x = SPACE + 4 * (pWidth + SPACE) + (pipes[i].x + pWidth);
		pipes[i].y = pipes[i].y = rand() % (28 - (GAP + 4)) + GAP + 4;
	}
}

void cycleGround(int i) {
	if (ground[i].x <= -128) {
		ground[i].x = 128 + (ground[i].x + 128);
	}
}

void draw() {
	int i;

	ClearDisplay;

	for (i = 0; i < 5; i++) {
		pipes[i].x -= PSPEED * dt;
		pipeCycle(i);
		drawSprite(pImage, pos(round(pipes[i].x), round(round(pipes[i].y))));
		drawSprite(pImage, pos(round(pipes[i].x), round(pipes[i].y - pHeight - GAP)));

	}

	for (i = 0; i < 2; i++) {
		ground[i].x -= PSPEED * dt;
		cycleGround(i);
		drawSprite(gImage, pos(ground[i].x, ground[i].y));
	}

	drawSprite(bird.image, pos(round(bird.x), round(bird.y)));
	UI();
	displayUpdate();
}

void scoreUpdate() {
	if (bird.x >= pipes[score % 5].x) {
		score++;
	}
}

void collision() {
	int i;

	if (bird.y + bHeight >= 30) {
		bird.hit = 1;
	}

	for (i = 0; i < 5; i++) {
		if (bird.x + bWidth >= pipes[i].x && bird.x <= pipes[i].x + pWidth) {
			if (!(bird.y + bHeight < pipes[i].y && bird.y > pipes[i].y - GAP)) {
				bird.hit = 1;
			}
		}
	}
}

void difficulty() {
	if (oldScore != score) {
		if (GAP > 16 && score % 2 == 1) {
			GAP--;
		}
		else if (score % 2 == 1) {
			PSPEED++;
		}
	}
	oldScore = score;

}

void game() {
	int i;

	ClearDisplay;
	printText("Ready", pos(53, 7));
	drawSprite(bird.image, pos(round(bird.x), round(bird.y)));
	for (i = 0; i < 2; i++) {
		drawSprite(gImage, pos(ground[i].x, ground[i].y));
	}
	displayUpdate();
	delay(1000);

	ClearDisplay;
	printText("3", pos(62, 7));
	drawSprite(bird.image, pos(round(bird.x), round(bird.y)));
	for (i = 0; i < 2; i++) {
		drawSprite(gImage, pos(ground[i].x, ground[i].y));
	}
	displayUpdate();
	delay(1000);

	ClearDisplay;
	printText("2", pos(62, 7));
	drawSprite(bird.image, pos(round(bird.x), round(bird.y)));
	for (i = 0; i < 2; i++) {
		drawSprite(gImage, pos(ground[i].x, ground[i].y));
	}
	displayUpdate();
	delay(1000);

	ClearDisplay;
	printText("1", pos(62, 7));
	drawSprite(bird.image, pos(round(bird.x), round(bird.y)));
	for (i = 0; i < 2; i++) {
		drawSprite(gImage, pos(ground[i].x, ground[i].y));
	}
	displayUpdate();
	delay(1000);

	jump();
	startTimer();
	while (gameON) {
		dt = stopTimer();
		startTimer();

		gravity();
		glide();
		scoreUpdate();
		collision();
		difficulty();

		if (bt4) {
			jump();
			button4 = 0;
		}
		if (bt3) {
			dash();
			button3 = 0;
		}

		if (bt2) {
			bird.y += 1;
			button2 = 0;
		}

		if (bird.hit) {
			gameON = 0;

			bird.x = 10;
			bird.y = 10;

			bird.hit = 0;
			bird.y_vel = 0;

			for (i = 0; i < 5; i++) {
				pipes[i].x = 128 + i * (pWidth + SPACE);
				pipes[i].y = rand() % (28 - (GAP + 4)) + GAP + 4;
			}

			ground[0].x = 0;
			ground[1].x = 127;

			time = 0;
			c = 0;
			fps = 0;
		}

		draw();
	}
}

