#include "pacman.h"

Pacman::Pacman()
{
	pac_cur = pac_left[0];
	PAC_VEL = 8 * scale;
	int pacRenderSize = 24 * scale;
	renderSize = {0, 0, pacRenderSize, pacRenderSize};

	if (!modeIdx)
	{
		pac_cur = pac_left[0];
		int X = TILE_WIDTH * pac_coor[curLevel - 1][0].first;
		int Y = TILE_WIDTH * pac_coor[curLevel - 1][0].second;
		pacBox = {posX + X, posY + Y, TILE_WIDTH, TILE_WIDTH};
		pac_animIdx = 0;
		nextDir = -1;
		pac_d = 0;
	}
	else
	{
		int idx = connection_state == "server" ? 0 : 1;
		int X = TILE_WIDTH * pac_coor[curLevel - 1][idx].first;
		int Y = TILE_WIDTH * pac_coor[curLevel - 1][idx].second;
		pacBox = {posX + X, posY + Y, TILE_WIDTH, TILE_WIDTH};
		if (!idx)
		{
			pac_cur = pac_left[0];
			pac_d = 0;
		}
		else
		{
			pac_cur = pac_right[0];
			pac_d = 2;
		}
		pac_animIdx = 0;
		nextDir = -1;
	}
	initPlayer();
}

void Pacman::render_other_player()
{
	int x = other_pac_d;
	SDL_Texture *cur_texture = nullptr;
	switch (x)
	{
	case 0:
		cur_texture = pac_left[other_pac_animIdx].mTexture;
		break;
	case 1:
		cur_texture = pac_down[other_pac_animIdx].mTexture;
		break;
	case 2:
		cur_texture = pac_right[other_pac_animIdx].mTexture;
		break;
	case 3:
		cur_texture = pac_up[other_pac_animIdx].mTexture;
		break;
	}
	// cur_texture.render(other_pac_box.x + TILE_WIDTH / 8, other_pac_box.y + TILE_WIDTH / 8, &renderSize);
	SDL_Rect renderRectBox = {other_pac_box.x + TILE_WIDTH / 8, other_pac_box.y + TILE_WIDTH / 8, renderSize.w, renderSize.h};
	SDL_RenderCopy(gRenderer, cur_texture, NULL, &renderRectBox);
	// pac_right[0].render(0, 0, &renderSize);
}

void Pacman::reset()

{
	if (!modeIdx)
	{
		pac_cur = pac_left[0];
		int X = TILE_WIDTH * pac_coor[curLevel - 1][0].first;
		int Y = TILE_WIDTH * pac_coor[curLevel - 1][0].second;
		pacBox = {posX + X, posY + Y, TILE_WIDTH, TILE_WIDTH};
		pac_animIdx = 0;
		nextDir = -1;
		pac_d = 0;
	}
	else
	{
		int idx = connection_state == "server" ? 0 : 1;
		int X = TILE_WIDTH * pac_coor[curLevel - 1][idx].first;
		int Y = TILE_WIDTH * pac_coor[curLevel - 1][idx].second;
		pacBox = {posX + X, posY + Y, TILE_WIDTH, TILE_WIDTH};
		if (!idx)
		{
			pac_cur = pac_left[0];
			pac_d = 0;
		}
		else
		{
			pac_cur = pac_right[0];
			pac_d = 2;
		}
		pac_animIdx = 0;
		nextDir = -1;
	}
}

void Pacman::eat(bool flag)
{
	int disEat = TILE_WIDTH * scale / 4;
	if (!flag)
	{
		int Gx = (pacBox.x + disEat - posX) / TILE_WIDTH;
		int Gy = (pacBox.y + disEat - posY) / TILE_WIDTH;
		if (isCoin[curLevel - 1][Gy][Gx])
		{
			// Sounds::getInstance()->playMunch();
			isCoin[curLevel - 1][Gy][Gx] = false;
			score[0]++;
			levelScore[curLevel - 1][0]++;
		}
	}
	else
	{
		int Gx = (other_pac_box.x + disEat - posX) / TILE_WIDTH;
		int Gy = (other_pac_box.y + disEat - posY) / TILE_WIDTH;
		if (isCoin[curLevel - 1][Gy][Gx])
		{
			Sounds::getInstance()->playMunch();
			isCoin[curLevel - 1][Gy][Gx] = false;
			score[1]++;
			levelScore[curLevel - 1][1]++;
		}
	}
}

void Pacman::death()
{
	// pacBox.x += 16 * dx[d];
	// pacBox.y += 16 * dy[d];
	lifes[0]--;
}

void Pacman::move(Tile *tiles[])
{
	changeDir(tiles);
	switch (pac_d)
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
	switch (pac_d)
	{
	case 0:
		pac_cur = pac_left[pac_animIdx];
		break;
	case 1:
		pac_cur = pac_down[pac_animIdx];
		break;
	case 2:
		pac_cur = pac_right[pac_animIdx];
		break;
	case 3:
		pac_cur = pac_up[pac_animIdx];
		break;
	}
	pac_animIdx = (pac_animIdx + 1) % 4;
}

void Pacman::render()
{
	int disp = TILE_WIDTH / 8;
	pac_cur.render(pacBox.x + disp, pacBox.y + disp, &renderSize);
}

void Pacman::handleEvent(SDL_Event &e)
{
	switch (e.key.keysym.sym)
	{
	case SDLK_LEFT:
		if (pac_d != 0)
			nextDir = 0;
		break;
	case SDLK_DOWN:
		if (pac_d != 1)
			nextDir = 1;
		break;
	case SDLK_RIGHT:
		if (pac_d != 2)
			nextDir = 2;
		break;
	case SDLK_UP:
		if (pac_d != 3)
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
			pac_d = 0;
		pacBox.x += PAC_VEL;
		break;
	case 1:
		pacBox.y = pacBox.y + PAC_VEL;
		if (!Grid::touchesWall(pacBox, tiles))
			pac_d = 1;
		pacBox.y -= PAC_VEL;
		break;
	case 2:
		pacBox.x = pacBox.x + PAC_VEL;
		if (!Grid::touchesWall(pacBox, tiles))
			pac_d = 2;
		pacBox.x -= PAC_VEL;
		break;
	case 3:
		pacBox.y = pacBox.y - PAC_VEL;
		if (!Grid::touchesWall(pacBox, tiles))
			pac_d = 3;
		pacBox.y += PAC_VEL;
		break;
	}
	if (pac_d == nextDir)
		nextDir = -1;
}