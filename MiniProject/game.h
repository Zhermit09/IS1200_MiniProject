#ifndef _GAME_
#define _GAME_
#include "io.h"

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
#endif // end of _GAME_