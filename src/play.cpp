#include "play.h"

Play::Play() {}

void Play::start() {
  std::string url = "Assets/levels/level";
  char c = '0' + curLevel;
  url += c;
  url += ".map";
  grid.loadTiles(url);
  curState = "play";
}

void Play::run() {
  pacman.move(grid.tiles);
  pacman.animate();
  ghost.move(grid.tiles);
  ghost.animate();
  grid.render();
  ghost.render();
  pacman.render();
}

void Play::handleEvent(SDL_Event &e) { pacman.handleEvent(e); }