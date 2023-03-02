#ifndef _GAME_
#define _GAME_
#include "io.h"

#define pos(x,y) (struct Vec){x,y}

struct Bird {
	struct Sprite image;
	
	double x;
	double y;

	int hit;

	double y_vel;
	double x_vel;

};

struct Pipe {
	double x;
	double y;

};

struct Ground {
	double x;
	double y;
};

struct Bird bird;
struct Pipe pipes[5];
struct Ground ground[2];

struct Sprite pImage;
struct Sprite gImage;

void gameSetup();
void game();
void scoreCheck();
#endif // end of _GAME_