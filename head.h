#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include <bits/stdc++.h>

// TODO: Remove the debugging statements later!
using namespace std;

inline string to_string(char c)
{
	return string(1, c);
}
inline string to_string(string s)
{
	return s;
}
inline string to_string(const char *s)
{
	return string(s);
}
inline string to_string(bool b)
{
	return (b ? "true" : "false");
}
inline string to_string(vector<bool> v)
{
	string res;
	for (int i = 0; i < (int)v.size(); i++)
		res += char('0' + v[i]);
	return res;
}
template <typename A, typename B>
inline string to_string(pair<A, B> p)
{
	return "(" + to_string(p.first) + ", " + to_string(p.second) + ")";
}
template <typename A, typename B, typename C>
inline string to_string(tuple<A, B, C> p)
{
	return "(" + to_string(get<0>(p)) + ", " + to_string(get<1>(p)) + ", " + to_string(get<2>(p)) + ")";
}
template <typename A, typename B, typename C, typename D>
inline string to_string(tuple<A, B, C, D> p)
{
	return "(" + to_string(get<0>(p)) + ", " + to_string(get<1>(p)) + ", " + to_string(get<2>(p)) + ", " + to_string(get<3>(p)) + ")";
}

template <typename A>
inline string to_string(A v)
{
	bool first = true;
	string res = "{";
	for (const auto &x : v)
	{
		if (!first)
		{
			res += ", ";
		}
		first = false;
		res += to_string(x);
	}
	res += "}";
	return res;
}

// Options
inline bool noMusic = false;
inline bool noSound = false;

// Music
inline Mix_Chunk *death = nullptr;
inline Mix_Chunk *start = nullptr;
inline Mix_Chunk *eatCoin = nullptr;
inline Mix_Chunk *pill = nullptr;
inline Mix_Chunk *eatGhost = nullptr;

inline SDL_Renderer *gRenderer = nullptr;
inline SDL_Window *gWindow = nullptr;
inline int SCREEN_WIDTH = 1400;
inline int SCREEN_HEIGHT = 1000;
inline int LEVEL_WIDTH = 800;
inline int LEVEL_HEIGHT = 900;
inline double scale = 1.0;
inline int posX = 300;
inline int posY = 150;
inline SDL_Color WHITE_COLOR = {255, 255, 255, 255};
inline SDL_Color YELLOW_COLOR = {255, 247, 11, 255};
inline SDL_Color GRAY_COLOR = {191, 191, 191, 255};
inline SDL_Color RED_COLOR = {255, 0, 0, 255};
inline SDL_Color GREEN_COLOR = {0, 255, 0, 255};
inline SDL_Color BLUE_COLOR = {0, 0, 255, 255};
inline std::string curState = "level";
inline int curLevel = 1;

inline int corners[4][2] = {{posX + 32, posY + 32},
							{posX + 32, posY + 32 * 23},
							{posX + 32 * 23, posY + 32 * 23},
							{posX + 32 * 23, posY + 32}};

inline const int TILE_WIDTH = 32;
inline const int TILE_HEIGHT = 32;
inline const int TOTAL_TILES = 625;
inline const int TOTAL_TILE_SPRITES = 3;
inline const int ROWS = 25;
inline const int COLS = 25;
inline const int interval = 90;
inline int counter = 0;
inline bool isRandom = false;
inline int lives = 3;

inline int dx[4] = {-1, 0, 1, 0};
inline int dy[4] = {0, 1, 0, -1};

inline std::pair<int, int> pac_coor[5] = {{12, 12}, {12, 13}, {12, 15}, {12, 13}, {12, 12}};
inline std::pair<int, int> ghost_coor[4] = {{1, 1}, {1, 23}, {23, 23}, {23, 1}};

inline TTF_Font *smallFont = nullptr;
inline TTF_Font *font = nullptr;
inline TTF_Font *largeFont = nullptr;
inline TTF_Font *veryLargeFont = nullptr;
inline TTF_Font *hugeFont = nullptr;

inline SDL_Texture *GRASS = nullptr;
inline SDL_Texture *BRICK = nullptr;
inline SDL_Texture *BLACK = nullptr;
inline SDL_Texture *resumeBack = nullptr;
inline SDL_Texture *menuBack = nullptr, *levelsBack = nullptr,
				   *winBack = nullptr, *loseBack = nullptr,
				   *soundBack = nullptr, *quitBack = nullptr,
				   *gameBack = nullptr;

inline SDL_Rect pacBox = {posX + 32, posY + 32, 32, 32};
inline bool first_time = false;

inline int lifes = 3;

inline int score = 0;

inline bool checkCollision(SDL_Rect a, SDL_Rect b)
{
	// The sides of the rectangles
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	// Calculate the sides of rect A
	leftA = a.x;
	rightA = a.x + a.w;
	topA = a.y;
	bottomA = a.y + a.h;

	// Calculate the sides of rect B
	leftB = b.x;
	rightB = b.x + b.w;
	topB = b.y;
	bottomB = b.y + b.h;

	// If any of the sides from A are outside of B
	if (bottomA <= topB)
	{
		return false;
	}

	if (topA >= bottomB)
	{
		return false;
	}

	if (rightA <= leftB)
	{
		return false;
	}

	if (leftA >= rightB)
	{
		return false;
	}

	// If none of the sides from A are outside B
	return true;
}

inline bool isCoin[5][25][25] = {0};
inline int totalCoins[5] = {0};

// inline int areaOfIntersection(SDL_Rect &a, SDL_Rect &b)
// {

// 	// The sides of the rectangles
// 	int leftA, leftB;
// 	int rightA, rightB;
// 	int topA, topB;
// 	int bottomA, bottomB;

// 	// Calculate the sides of rect A
// 	leftA = a.x;
// 	rightA = a.x + a.w;
// 	topA = a.y;
// 	bottomA = a.y + a.h;

// 	// Calculate the sides of rect B
// 	leftB = b.x;
// 	rightB = b.x + b.w;
// 	topB = b.y;
// 	bottomB = b.y + b.h;

// 	// If any of the sides from A are outside of B
// 	if (bottomA <= topB)
// 	{
// 		return 0;
// 	}

// 	if (topA >= bottomB)
// 	{
// 		return 0;
// 	}

// 	if (rightA <= leftB)
// 	{
// 		return 0;
// 	}

// 	if (leftA >= rightB)
// 	{
// 		return 0;
// 	}
// }

inline int matrix[5][25][25];