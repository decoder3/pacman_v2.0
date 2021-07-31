#pragma once
#include "head.h"

class Tile

{
public:
  // Initializes position and type
  Tile(int x, int y, int tileType);

  // Shows the tile
  void render();

  // Get the tile type
  int getType();

  // Get the collision box
  SDL_Rect getBox();

private:
  // The attributes of the tile
  SDL_Rect tileBox;

  // The tile type
  int tileType;
};