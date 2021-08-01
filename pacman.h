#pragma once
#include "LTexture.h"
#include "Tile.h"
#include "grid.h"
#include "head.h"
#include "sounds.h"

class Pacman
{
	LTexture pac_cur;
	LTexture pac_left[4], pac_right[4], pac_up[4], pac_down[4];
	SDL_Rect renderSize;
	int nextDir;

public:
	Pacman();
	int PAC_VEL;
	void handleEvent(SDL_Event &e);
	void move(Tile *tiles[]);
	void changeDir(Tile *tiles[]);
	void death();
	void animate();
	void initPlayer();
	void render();
	void reset();
	void eat(bool flag);

	int getX();
	int getY();
	int getDir();
};