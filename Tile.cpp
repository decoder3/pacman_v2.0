#include "Tile.h"

Tile::Tile(int x, int y, int tileTypeT)
{
	// Get the offsets
	tileBox.x = x;
	tileBox.y = y;

	// Set the collision box
	tileBox.w = TILE_WIDTH;
	tileBox.h = TILE_HEIGHT;

	// Get the tile type
	tileType = tileTypeT;
}

int Tile::getType() { return tileType; }

SDL_Rect Tile::getBox() { return tileBox; }

void Tile::render()
{
	SDL_RenderCopy(gRenderer, (tileType ? BRICK : BLACK), NULL, &tileBox);
}