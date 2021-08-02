#pragma once
#include "LTexture.h"
#include "Tile.h"
#include "head.h"

class Grid
{
public:
	Grid();
	~Grid();
	Tile *tiles[TOTAL_TILES];
	static bool touchesWall(SDL_Rect box, Tile *tiles[]);
	SDL_Rect coinRenderSize;
	enum tileTypes
	{
		GRASS,
		BRICK
	};
	LTexture coin;
	bool loadTiles(std::string map_path);
	void render();
};