#include "app.h"
#include "head.h"
#include "level.h"
#include "pacman.h"
#include "play.h"
using namespace std;

int main() {
  App app;
  app.Init();
  Play play;
  Level levels;
  SDL_Event e;
  bool flag = true;
  while (flag) {
    while (SDL_PollEvent(&e) != 0) {
      if (e.type == SDL_QUIT) {
        flag = false;
        break;
      }
      if (curState == "level")
        levels.handleEvent(e);
      else if (curState == "play")
        play.handleEvent(e);
    }
    SDL_SetRenderDrawColor(gRenderer, 0xff, 0xff, 0xff, 0xff);
    SDL_RenderClear(gRenderer);

    if (curState == "level") {
      levels.render();
    } else if (curState == "start") {
      play.start();
    } else if (curState == "play") {
      play.run();
    }
    SDL_RenderPresent(gRenderer);
    SDL_Delay(100);
  }
}