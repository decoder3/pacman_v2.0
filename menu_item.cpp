#include "menu_item.h"

MenuItem::MenuItem() {
  x = 0, y = 0;
  selected = false;
  isAlt = false;
  isAltSelected = false;
}

void MenuItem::toggleMenuItem() {
  if (isAlt) {
    isAltSelected = isAltSelected ? false : true;
  }
}

void MenuItem::setCurrentItem(bool val) { selected = val; }

LTexture *MenuItem::getCurrentItem() {
  if (selected) {
    return (isAlt ? &itemAltSel : &itemSel);
  } else {
    return (isAlt ? &itemAlt : &item);
  }
}

void MenuItem::render() { getCurrentItem()->render(x, y); }