#ifndef _GAME_
#define _GAME_
#include "io.h"

#define pos(x,y) (struct Vec){x,y}
#define scale(x,y) (struct Vec){x,y}

struct Bird {
	struct Sprite image;
	
	struct Vec pos;
	int hit;
	float vel;

};

struct Pipe {

	struct Vec pos;

};

struct Bird bird;

void gameSetup();
void game();
void scoreCheck(int score);
#endif // end of _GAME_