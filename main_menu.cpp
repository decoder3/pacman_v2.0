#include "main_menu.h"
MainMenu::MainMenu()
{
	x = 200;
	y = 100;
	isActive = true;
	numItems = 4;
	height = 50;
	curItem = 0;
	for (int i = 0; i < 4; i++)
	{
		items[i] = new MenuItem();
	}
	items[0]->selected = true;
	loadMedia();
}

void MainMenu::render()
{
	if (isActive)
	{
		for (int i = 0; i < 4; i++)
		{
			items[i]->render();
		}
	}
}

void MainMenu::loadMedia()
{
	items[0]->item.loadFromRenderedText(largeFont, "Play", GRAY_COLOR);
	items[0]->itemSel.loadFromRenderedText(veryLargeFont, "Play", WHITE_COLOR);
	items[1]->item.loadFromRenderedText(largeFont, "Controls", GRAY_COLOR);
	items[1]->itemSel.loadFromRenderedText(veryLargeFont, "Controls",
										   WHITE_COLOR);
	items[2]->item.loadFromRenderedText(largeFont, "Stats", GRAY_COLOR);
	items[2]->itemSel.loadFromRenderedText(veryLargeFont, "Stats", WHITE_COLOR);
	items[3]->item.loadFromRenderedText(largeFont, "Quit", GRAY_COLOR);
	items[3]->itemSel.loadFromRenderedText(veryLargeFont, "Quit", WHITE_COLOR);
	for (int i = 0; i < 4; i++)
	{
		items[i]->x = x;
		items[i]->y = i * height + y;
	}
}

void MainMenu::selectNext()
{
	items[curItem]->selected = false;
	curItem = (curItem + 1) % numItems;
	items[curItem]->selected = true;
}

void MainMenu::selectPrev()
{
	items[curItem]->selected = false;
	curItem = (curItem - 1 + numItems) % numItems;
	items[curItem]->selected = true;
}