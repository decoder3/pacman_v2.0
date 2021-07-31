#include "pacman.h"

Pacman::Pacman()
{
	pac_cur = pac_left[0];
	int X = 32 * pac_coor[curLevel - 1].first;
	int Y = 32 * pac_coor[curLevel - 1].second;
	pacBox = {posX + X, posY + Y, PAC_WIDTH, PAC_HEIGHT};
	renderSize = {0, 0, 24, 24};
	animIdx = 0;
	nextDir = -1;
	d = 0;
	initPlayer();
}

void Pacman::reset()

{
	pac_cur = pac_left[0];
	int X = 32 * pac_coor[curLevel - 1].first;
	int Y = 32 * pac_coor[curLevel - 1].second;
	pacBox = {posX + X, posY + Y, PAC_WIDTH, PAC_HEIGHT};
	animIdx = 0;
	nextDir = -1;
	d = 0;
}

void Pacman::eat()
{
	int Gx = (pacBox.x + 4 - posX) / 32;
	int Gy = (pacBox.y + 4 - posY) / 32;
	if (isCoin[curLevel - 1][Gy][Gx])
	{
		Sounds::getInstance()->playMunch();
		isCoin[curLevel - 1][Gy][Gx] = false;
		score++;
	}
}

void Pacman::death()
{
	// pacBox.x += 16 * dx[d];
	// pacBox.y += 16 * dy[d];
	lifes--;
}

void Pacman::move(Tile *tiles[])
{
	changeDir(tiles);
	switch (d)
	{
	case 0:
		pacBox.x = pacBox.x - PAC_VEL;
		if (Grid::touchesWall(pacBox, tiles))
		{
			pacBox.x += PAC_VEL;
		}
		break;
	case 1:
		pacBox.y = pacBox.y + PAC_VEL;
		if (Grid::touchesWall(pacBox, tiles))
		{
			pacBox.y -= PAC_VEL;
		}
		break;
	case 2:
		pacBox.x = pacBox.x + PAC_VEL;
		if (Grid::touchesWall(pacBox, tiles))
		{
			pacBox.x -= PAC_VEL;
		}
		break;
	case 3:
		pacBox.y = pacBox.y - PAC_VEL;
		if (Grid::touchesWall(pacBox, tiles))
		{
			pacBox.y += PAC_VEL;
		}
		break;
	}
}

void Pacman::initPlayer()
{
	pac_left[0].loadFromFile("Assets/Images/pac_left1.png");
	pac_left[1].loadFromFile("Assets/Images/pac_left2.png");
	pac_left[2].loadFromFile("Assets/Images/pac_left1.png");
	pac_left[3].loadFromFile("Assets/Images/pacman.png");
	pac_right[0].loadFromFile("Assets/Images/pac_right1.png");
	pac_right[1].loadFromFile("Assets/Images/pac_right2.png");
	pac_right[2].loadFromFile("Assets/Images/pac_right1.png");
	pac_right[3].loadFromFile("Assets/Images/pacman.png");
	pac_up[0].loadFromFile("Assets/Images/pac_up1.png");
	pac_up[1].loadFromFile("Assets/Images/pac_up2.png");
	pac_up[2].loadFromFile("Assets/Images/pac_up1.png");
	pac_up[3].loadFromFile("Assets/Images/pacman.png");
	pac_down[0].loadFromFile("Assets/Images/pac_down1.png");
	pac_down[1].loadFromFile("Assets/Images/pac_down2.png");
	pac_down[2].loadFromFile("Assets/Images/pac_down1.png");
	pac_down[3].loadFromFile("Assets/Images/pacman.png");
}

void Pacman::animate()
{
	switch (d)
	{
	case 0:
		pac_cur = pac_left[animIdx];
		break;
	case 1:
		pac_cur = pac_down[animIdx];
		break;
	case 2:
		pac_cur = pac_right[animIdx];
		break;
	case 3:
		pac_cur = pac_up[animIdx];
		break;
	}
	animIdx = (animIdx + 1) % 4;
}

void Pacman::render()
{
	pac_cur.render(pacBox.x + 4, pacBox.y + 4, &renderSize);
}

void Pacman::handleEvent(SDL_Event &e)
{
	switch (e.key.keysym.sym)
	{
	case SDLK_LEFT:
		if (d != 0)
			nextDir = 0;
		break;
	case SDLK_DOWN:
		if (d != 1)
			nextDir = 1;
		break;
	case SDLK_RIGHT:
		if (d != 2)
			nextDir = 2;
		break;
	case SDLK_UP:
		if (d != 3)
			nextDir = 3;
		break;
	}
}

void Pacman::changeDir(Tile *tiles[])
{
	if (nextDir == -1)
		return;
	bool flag = false;
	switch (nextDir)
	{
	case 0:
		pacBox.x = pacBox.x - PAC_VEL;
		if (!Grid::touchesWall(pacBox, tiles))
			d = 0;
		pacBox.x += PAC_VEL;
		break;
	case 1:
		pacBox.y = pacBox.y + PAC_VEL;
		if (!Grid::touchesWall(pacBox, tiles))
			d = 1;
		pacBox.y -= PAC_VEL;
		break;
	case 2:
		pacBox.x = pacBox.x + PAC_VEL;
		if (!Grid::touchesWall(pacBox, tiles))
			d = 2;
		pacBox.x -= PAC_VEL;
		break;
	case 3:
		pacBox.y = pacBox.y - PAC_VEL;
		if (!Grid::touchesWall(pacBox, tiles))
			d = 3;
		pacBox.y += PAC_VEL;
		break;
	}
	if (d == nextDir)
		nextDir = -1;
}