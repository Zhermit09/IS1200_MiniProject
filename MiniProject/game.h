#ifndef _GAME_
#define _GAME_
#include "io.h"

#define pos(x,y) (struct Vec){x,y}
#define scale(x,y) (struct Vec){x,y}

struct Bird {
	struct Sprite image;
	
	struct Vec pos;
	int hit;
	double y_vel;
	double x_vel;

};

struct Pipe {
	struct Vec pos;

};

struct Bird bird;
struct Pipe pipes[5];


void gameSetup();
void game();
void scoreCheck(int score);
#endif // end of _GAME_