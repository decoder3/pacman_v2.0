#pragma once
#include "LTexture.h"
#include "head.h"

class Level {
  int idx;
  LTexture levels[6];
  int lWidth, lHeight;
  int pos[5][2];

public:
  Level();
  void init();
  void handleEvent(SDL_Event &e);
  void render();
  bool intersect(int i, int x, int y);
};
