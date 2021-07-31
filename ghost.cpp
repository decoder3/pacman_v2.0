#include "ghost.h"

std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

Ghost::Ghost()
{
	renderSize = {0, 0, 24, 24};
	int X = 32 * 23;
	mBox[0] = {posX + 32, posY + 32, 32, 32};
	mBox[1] = {posX + 32, posY + X, 32, 32};
	mBox[2] = {posX + X, posY + X, 32, 32};
	mBox[3] = {posX + X, posY + 32, 32, 32};
	state[0] = state[2] = 2;
	state[1] = state[3] = 0;
	for (int i = 0; i < 4; i++)
	{
		animIdx[i] = 0;
		d[i] = 0;
		cur[i] = sprites[i][0][0];
	}
	GHOST_VEL = 8;
	init();
}

void Ghost::reset()
{
	int X = 32 * 23;
	mBox[0] = {posX + 32, posY + 32, 32, 32};
	mBox[1] = {posX + 32, posY + X, 32, 32};
	mBox[2] = {posX + X, posY + X, 32, 32};
	mBox[3] = {posX + X, posY + 32, 32, 32};
	isRandom = false;
	for (int i = 0; i < 4; i++)
	{
		animIdx[i] = 0;
		d[i] = 0;
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
		cur[i] = sprites[i][d[i]][animIdx[i]];
		animIdx[i] = (animIdx[i] + 1) % 2;
	}
}

void Ghost::render()
{
	for (int i = 0; i < 4; i++)
	{
		cur[i].render(mBox[i].x + 4, mBox[i].y + 4, &renderSize);
	}
}

std::vector<int> Ghost::checkDirections(int i, Tile *tiles[])
{
	std::vector<int> temp;
	for (int j = 0; j < 4; j++)
	{
		int disX = GHOST_VEL * dx[j];
		int disY = GHOST_VEL * dy[j];
		mBox[i].x += disX;
		mBox[i].y += disY;
		bool flag = true;
		if (Grid::touchesWall(mBox[i], tiles))
			flag = false;
		// if (flag)
		// {
		// 	for (int k = 0; k < 4; k++)
		// 	{
		// 		if (k != i)
		// 		{
		// 			if (checkCollision(mBox[i], mBox[k]))
		// 			{
		// 				flag = false;
		// 				break;
		// 			}
		// 		}
		// 	}
		// }
		mBox[i].x -= disX;
		mBox[i].y -= disY;
		if (flag)
			temp.push_back(j);
	}
	auto it = find(begin(temp), end(temp), d[i]);
	if (it != end(temp))
	{
		int x = (d[i] + 2) % 4;
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
			int x = (d[i] + 2) % 4;
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
		d[idx] = -1;
		return;
	}
	int x = rng() % n;
	d[idx] = available_directions[x];
}

void Ghost::move(Tile *tiles[])
{
	if (counter % 60 == 0)
	{
		for (int i = 0; i < 4; i++)
		{
			d[i] = (d[i] + 2) % 4;
		}
		vector<int> temp = {0, 1, 2, 3};
		random_shuffle(begin(temp), end(temp));
		state[temp[0]] = state[temp[1]] = 0;
		state[temp[2]] = state[temp[3]] = 2;
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
		if (d[i] != -1)
		{
			int disX = GHOST_VEL * dx[d[i]];
			int disY = GHOST_VEL * dy[d[i]];
			mBox[i].x += disX;
			mBox[i].y += disY;
			if (Grid::touchesWall(mBox[i], tiles))
			{
				mBox[i].x -= disX;
				mBox[i].y -= disY;
			}
		}
		else
		{
			int x = rng() % 4;
			d[i] = x;
		}
	}
	// for (int i = 0; i < 4; i++)
	// {
	// 	int xx = (mBox[i].x - posX) / 32;
	// 	int yy = (mBox[i].y - posY) / 32;
	// cout << "{" << xx << ", " << yy << ", " << d[i] << ", " << state[i] << "} ";
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
			if (checkCollision(mBox[i], mBox[idx]))
			{
				if (d[i] == (d[idx] + 2) % 4)
				{
					d[idx] = (d[idx] + 2) % 4;
					state[idx] = 0;
				}
				d[i] = (d[i] + 2) % 4;
				checkIfDirectionSet[i] = checkIfDirectionSet[idx] = true;
				state[i] = 0;
				return;
			}
		}
	}
	int cx = (mBox[idx].x - posX) % 32;
	int cy = (mBox[idx].y - posY) % 32;
	if (cx || cy)
		return;
	if (!state[idx])
	{
		checkIfDirectionSet[idx] = true;
		findRandomDir(idx, tiles);
	}
	else
	{
		findDir(idx);
	}
}

void Ghost::findDir(int idx)
{
	int ix = (mBox[idx].x - posX) / 32;
	int iy = (mBox[idx].y - posY) / 32;
	int Ix, Iy;
	if (state[idx] == 1)
	{
		Ix = (corners[idx][0] - posX) / 32;
		Iy = (corners[idx][1] - posY) / 32;
	}
	else
	{
		Ix = (pacBox.x - posX) / 32;
		Iy = (pacBox.y - posY) / 32;
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
			if (X > 0 && Y > 0 && X < 24 && Y < 24 && !matrix[curLevel - 1][Y][X] &&
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
		assert(dd != -1);
		// if (dd == -1)
		// {
		// 	cout << idx << ": ";
		// 	cout << "{" << ix << ", " << iy << "} ";
		// 	cout << "{" << Ix << ", " << Iy << "}\n";
		// 	SDL_Delay(3000);
		// 	return;
		// }
		ps = {ps.first + dy[dd], ps.second + dx[dd]};
		if (ps == pd)
		{
			// for (int i = 0; i < 4; i++)
			// {
			// 	if (i != idx)
			// 	{
			// 		if (checkCollision(mBox[i], mBox[idx]))
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
			d[idx] = (dd + 2) % 4;
			return;
		}
	}
}

int Ghost::checkCollissionWithPacman()
{
	for (int i = 0; i < 4; i++)
	{
		SDL_Rect a = mBox[i];
		SDL_Rect b = pacBox;
		int fact = 8;
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
// 	mBox[x].x += 16 * dx[d[x]];
// 	mBox[x].y += 16 * dy[d[x]];
// }