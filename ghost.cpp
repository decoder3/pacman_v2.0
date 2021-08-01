#include "ghost.h"

std::mt19937 rngg(std::chrono::steady_clock::now().time_since_epoch().count());

Ghost::Ghost()
{
	int renderWidth = 24 * scale;
	renderSize = {0, 0, renderWidth, renderWidth};
	int X = TILE_WIDTH * 23;
	ghost_mBox[0] = {posX + TILE_HEIGHT, posY + TILE_HEIGHT, TILE_HEIGHT, TILE_HEIGHT};
	ghost_mBox[1] = {posX + TILE_HEIGHT, posY + X, TILE_HEIGHT, TILE_HEIGHT};
	ghost_mBox[2] = {posX + X, posY + X, TILE_HEIGHT, TILE_HEIGHT};
	ghost_mBox[3] = {posX + X, posY + TILE_HEIGHT, TILE_HEIGHT, TILE_HEIGHT};
	state[0] = state[2] = 1;
	state[1] = state[3] = 0;
	for (int i = 0; i < 4; i++)
	{
		ghost_animIdx[i] = 0;
		ghost_d[i] = 0;
		cur[i] = sprites[i][0][0];
	}
	GHOST_VEL = 8 * scale;
	init();
}

void Ghost::reset()
{
	int X = TILE_WIDTH * 23;
	ghost_mBox[0] = {posX + TILE_HEIGHT, posY + TILE_HEIGHT, TILE_HEIGHT, TILE_HEIGHT};
	ghost_mBox[1] = {posX + TILE_HEIGHT, posY + X, TILE_HEIGHT, TILE_HEIGHT};
	ghost_mBox[2] = {posX + X, posY + X, TILE_HEIGHT, TILE_HEIGHT};
	ghost_mBox[3] = {posX + X, posY + TILE_HEIGHT, TILE_HEIGHT, TILE_HEIGHT};
	isRandom = false;
	for (int i = 0; i < 4; i++)
	{
		ghost_animIdx[i] = 0;
		ghost_d[i] = 0;
		cur[i] = sprites[i][0][0];
	}
}

void Ghost::init()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			for (int k = 0; k < 2; k++)
			{
				std::string url = "Assets/Ghosts/ghost_";
				char c = '0' + i;
				char d = '0' + j;
				char e = '0' + k;
				url += c;
				url += d;
				url += e;
				url += ".png";
				sprites[i][j][k].loadFromFile(url);
			}
		}
	}
}

void Ghost::animate()
{
	for (int i = 0; i < 4; i++)
	{
		cur[i] = sprites[i][ghost_d[i]][ghost_animIdx[i]];
		ghost_animIdx[i] = (ghost_animIdx[i] + 1) % 2;
	}
}

void Ghost::render()
{
	for (int i = 0; i < 4; i++)
	{
		int disp = TILE_WIDTH / 8;
		cur[i].render(ghost_mBox[i].x + disp, ghost_mBox[i].y + disp, &renderSize);
	}
}

std::vector<int> Ghost::checkDirections(int i, Tile *tiles[])
{
	std::vector<int> temp;
	for (int j = 0; j < 4; j++)
	{
		int disX = GHOST_VEL * dx[j];
		int disY = GHOST_VEL * dy[j];
		ghost_mBox[i].x += disX;
		ghost_mBox[i].y += disY;
		bool flag = true;
		if (Grid::touchesWall(ghost_mBox[i], tiles))
			flag = false;
		// if (flag)
		// {
		// 	for (int k = 0; k < 4; k++)
		// 	{
		// 		if (k != i)
		// 		{
		// 			if (checkCollision(ghost_mBox[i], ghost_mBox[k]))
		// 			{
		// 				flag = false;
		// 				break;
		// 			}
		// 		}
		// 	}
		// }
		ghost_mBox[i].x -= disX;
		ghost_mBox[i].y -= disY;
		if (flag)
			temp.push_back(j);
	}
	auto it = find(begin(temp), end(temp), ghost_d[i]);
	if (it != end(temp))
	{
		int x = (ghost_d[i] + 2) % 4;
		auto it2 = find(begin(temp), end(temp), x);
		if (it2 != end(temp))
		{
			temp.erase(it2);
		}
	}
	else
	{
		int n = (int)temp.size();
		if (n > 1)
		{
			int x = (ghost_d[i] + 2) % 4;
			it = find(begin(temp), end(temp), x);
			if (it != end(temp))
			{
				temp.erase(it);
			}
		}
	}
	return temp;
}

void Ghost::findRandomDir(int idx, Tile *tiles[])
{
	std::vector<int> available_directions = checkDirections(idx, tiles);
	int n = (int)available_directions.size();
	if (!n)
	{
		ghost_d[idx] = -1;
		return;
	}
	int x = rngg() % n;
	ghost_d[idx] = available_directions[x];
}

void Ghost::move(Tile *tiles[])
{
	if (counter % 60 == 0)
	{
		for (int i = 0; i < 4; i++)
		{
			ghost_d[i] = (ghost_d[i] + 2) % 4;
		}
		vector<int> temp = {0, 1, 2, 3};
		random_shuffle(begin(temp), end(temp));
		state[temp[0]] = state[temp[1]] = 0;
		state[temp[2]] = state[temp[3]] = 1;
		counter++;
		return;
	}
	for (int i = 0; i < 4; i++)
	{
		checkIfDirectionSet[i] = false;
	}
	vector<int> temp = {0, 1, 2, 3};
	random_shuffle(begin(temp), end(temp));
	for (int j = 0; j < 4; j++)
	{
		int i = temp[j];
		if (!checkIfDirectionSet[i])
		{
			changeDir(i, tiles);
		}
		if (ghost_d[i] != -1)
		{
			int disX = GHOST_VEL * dx[ghost_d[i]];
			int disY = GHOST_VEL * dy[ghost_d[i]];
			ghost_mBox[i].x += disX;
			ghost_mBox[i].y += disY;
			if (Grid::touchesWall(ghost_mBox[i], tiles))
			{
				ghost_mBox[i].x -= disX;
				ghost_mBox[i].y -= disY;
			}
		}
		else
		{
			int x = rngg() % 4;
			ghost_d[i] = x;
		}
	}
	// for (int i = 0; i < 4; i++)
	// {
	// 	cout << "{" << ghost_mBox[i].x << ", " << ghost_mBox[i].y << ", " << posX << ", " << posY << "} ";
	// }
	// cout << endl;
	// for (int i = 0; i < 4; i++)
	// {
	// 	int xx = (ghost_mBox[i].x - posX) / TILE_WIDTH;
	// 	int yy = (ghost_mBox[i].y - posY) / TILE_WIDTH;
	// 	cout << "{" << xx << ", " << yy << ", " << d[i] << ", " << state[i] << "} ";
	// }
	// cout << endl;
	counter++;
}

void Ghost::changeDir(int idx, Tile *tiles[])
{
	vector<int> temp = {0, 1, 2, 3};
	random_shuffle(begin(temp), end(temp));
	for (int j = 0; j < 4; j++)
	{
		int i = temp[j];
		if (i != idx)
		{
			if (checkCollision(ghost_mBox[i], ghost_mBox[idx]))
			{
				if (ghost_d[i] == (ghost_d[idx] + 2) % 4)
				{
					ghost_d[idx] = (ghost_d[idx] + 2) % 4;
					state[idx] = 0;
				}
				ghost_d[i] = (ghost_d[i] + 2) % 4;
				checkIfDirectionSet[i] = checkIfDirectionSet[idx] = true;
				state[i] = 0;
				return;
			}
		}
	}
	int cx = (ghost_mBox[idx].x - posX) % TILE_WIDTH;
	int cy = (ghost_mBox[idx].y - posY) % TILE_WIDTH;
	if (cx || cy)
		return;
	// if (!state[idx])
	// {
	// 	checkIfDirectionSet[idx] = true;
	// 	findRandomDir(idx, tiles);
	// }
	// else
	// {
	findDir(idx);
	// }
}

void Ghost::findDir(int idx)
{
	cout << "idx " << state[idx] << endl;
	int ix = (ghost_mBox[idx].x - posX) / TILE_WIDTH;
	int iy = (ghost_mBox[idx].y - posY) / TILE_WIDTH;
	int Ix, Iy;
	if (state[idx] == 1)
	{
		// Ix = (corners[idx][0] - posX) / TILE_WIDTH;
		// Iy = (corners[idx][1] - posY) / TILE_WIDTH;
		Ix = (other_pac_box.x - posX) / TILE_WIDTH;
		Iy = (other_pac_box.y - posY) / TILE_WIDTH;
	}
	else
	{
		Ix = (pacBox.x - posX) / TILE_WIDTH;
		Iy = (pacBox.y - posY) / TILE_WIDTH;
	}
	std::pair<int, int> ps = {Iy, Ix}, pd = {iy, ix};
	int par[25][25];
	for (int i = 0; i < 25; i++)
	{
		for (int j = 0; j < 25; j++)
		{
			par[i][j] = -1;
		}
	}
	par[iy][ix] = 0;
	std::queue<std::pair<int, int>> q;
	q.push({iy, ix});
	while (!q.empty())
	{
		auto [y, x] = q.front();
		q.pop();
		for (int i = 0; i < 4; i++)
		{
			int X = x + dx[i];
			int Y = y + dy[i];
			if (X > 0 && Y > 0 && X < 24 && Y < 24 && (matrix[curLevel - 1][Y][X] != 1) &&
				par[Y][X] == -1)
			{
				par[Y][X] = (i + 2) % 4;
				q.push({Y, X});
			}
		}
	}
	while (true)
	{
		int dd = par[ps.first][ps.second];
		// TODO: take care of this situation. -- done
		// assert(dd != -1);
		if (dd == -1)
		{
			ghost_d[idx] = -1;
			return;
		}
		ps = {ps.first + dy[dd], ps.second + dx[dd]};
		if (ps == pd)
		{
			// for (int i = 0; i < 4; i++)
			// {
			// 	if (i != idx)
			// 	{
			// 		if (checkCollision(ghost_mBox[i], ghost_mBox[idx]))
			// 		{
			// 			d[i] = (d[i] + 2) % 4;
			// 			d[idx] = (d[idx] + 2) % 4;
			// 			checkIfDirectionSet[i] = checkIfDirectionSet[idx] = true;
			// 			state[i] = state[idx] = 0;
			// 			return;
			// 		}
			// 	}
			// }
			checkIfDirectionSet[idx] = true;
			ghost_d[idx] = (dd + 2) % 4;
			return;
		}
	}
}

int Ghost::checkCollissionWithPacman(SDL_Rect xBox)
{
	for (int i = 0; i < 4; i++)
	{
		SDL_Rect a = ghost_mBox[i];
		SDL_Rect b = xBox;
		int fact = 8 * scale;
		a.x += fact;
		a.y += fact;
		a.w -= 2 * fact;
		a.h -= 2 * fact;
		b.x += fact;
		b.y += fact;
		b.w -= 2 * fact;
		b.h -= 2 * fact;
		if (checkCollision(a, b))
			return i;
	}
	return -1;
}

// void Ghost::pacDeath(int x)
// {
// 	ghost_mBox[x].x += 16 * dx[d[x]];
// 	ghost_mBox[x].y += 16 * dy[d[x]];
// }