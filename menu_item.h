#pragma once
#include "LTexture.h"
#include "head.h"

class MenuItem {
public:
  int x, y;
  LTexture item, itemSel, itemAlt, itemAltSel;
  bool selected, isAlt, isAltSelected;
  void toggleMenuItem();
  void setCurrentItem(bool val);
  LTexture *getCurrentItem();
  MenuItem();
  void render();
};