#pragma once
#include "ghost.h"
#include "grid.h"
#include "head.h"
#include "pacman.h"

class Play {
  Grid grid;
  Pacman pacman;
  Ghost ghost;

public:
  Play();
  void run();
  void start();
  void handleEvent(SDL_Event &e);
};