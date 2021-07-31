#pragma once
#include "LTexture.h"
#include "Tile.h"
#include "grid.h"
#include "head.h"
#include "sounds.h"

class Pacman
{
	LTexture pac_left[4], pac_right[4], pac_up[4], pac_down[4];
	LTexture pac_cur;
	SDL_Rect renderSize;
	int d;

	int animIdx;
	int nextDir;

public:
	Pacman();
	static const int PAC_WIDTH = 32;
	static const int PAC_HEIGHT = 32;
	static const int PAC_VEL = 8;
	void handleEvent(SDL_Event &e);
	void move(Tile *tiles[]);
	void changeDir(Tile *tiles[]);
	void death();
	void animate();
	void initPlayer();
	void render();
	void reset();
	void eat();

	int getX();
	int getY();
	int getDir();
};