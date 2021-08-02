#pragma once
#include "head.h"
#include "menu_item.h"

class MainMenu {

public:
  int numItems;
  int x, y, height;
  MainMenu();
  MenuItem *items[4];
  int curItem;
  bool isActive;
  enum menuItems { PLAY, CONTROLS, STATS, QUIT };
  void render();
  void loadMedia();
  void selectNext();
  void selectPrev();
  void handleEvent();
};