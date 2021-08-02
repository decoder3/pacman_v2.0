#include "level.h"

Level::Level() {
  idx = 0;
  lWidth = 330;
  lHeight = 136;

  pos[0][0] = 99;
  pos[0][1] = 78;

  pos[1][0] = 1172;
  pos[1][1] = 78;

  pos[2][0] = 99;
  pos[2][1] = 712;

  pos[3][0] = 1172;
  pos[3][1] = 712;

  pos[4][0] = 636;
  pos[4][1] = 382;
  init();
}

void Level::init() {
  for (int i = 0; i < 6; i++) {
    std::string s = "Assets/levels/level_";
    char c = '0' + i;
    s += c;
    s += ".jpg";
    levels[i].loadFromFile(s);
  }
}

void Level::render() { levels[idx].render(0, 0); }

void Level::handleEvent(SDL_Event &e) {
  if (e.type == SDL_MOUSEMOTION) {
    int x, y;
    SDL_GetMouseState(&x, &y);
    bool flag = true;
    for (int i = 0; i < 5; i++) {
      if (intersect(i, x, y)) {
        idx = i + 1, flag = false;
        break;
      }
    }
    if (flag)
      idx = 0;
  } else if (e.type == SDL_MOUSEBUTTONDOWN) {
    int x, y;
    SDL_GetMouseState(&x, &y);
    for (int i = 0; i < 5; i++) {
      if (intersect(i, x, y)) {
        idx = 0;
        curState = "start";
        curLevel = i + 1;
        break;
      }
    }
  }
}

bool Level::intersect(int i, int x, int y) {
  if (x >= pos[i][0] && y >= pos[i][1] && x <= pos[i][0] + lWidth &&
      y <= pos[i][1] + lHeight)
    return true;
  return false;
}