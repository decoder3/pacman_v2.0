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

inline int modeIdx = 0;
inline string connection_state = "";

// Options
inline bool noMusic = false;
inline bool noSound = false;
// inline bool pause = false;

// Music
inline Mix_Chunk *death = nullptr;
inline Mix_Chunk *start = nullptr;
inline Mix_Chunk *eatCoin = nullptr;
inline Mix_Chunk *pill = nullptr;
inline Mix_Chunk *eatGhost = nullptr;

inline SDL_Renderer *gRenderer = nullptr;
inline SDL_Window *gWindow = nullptr;
inline double scale = 0.75;
inline int SCREEN_WIDTH = 1280;
inline int SCREEN_HEIGHT = 720;
inline int LEVEL_WIDTH = 800 * scale;
inline int LEVEL_HEIGHT = 800 * scale;
inline int posX = (SCREEN_WIDTH - LEVEL_WIDTH) / 2;
inline int posY = 100;
inline int winPosX = (1920 - SCREEN_WIDTH) / 2;
inline int winPosY = (1080 - SCREEN_HEIGHT) / 2;
inline SDL_Color WHITE_COLOR = {255, 255, 255, 255};
inline SDL_Color YELLOW_COLOR = {255, 247, 11, 255};
inline SDL_Color GRAY_COLOR = {191, 191, 191, 255};
inline SDL_Color RED_COLOR = {255, 0, 0, 255};
inline SDL_Color GREEN_COLOR = {0, 255, 0, 255};
inline SDL_Color BLUE_COLOR = {0, 0, 255, 255};
inline std::string curState = "level";
inline int curLevel = 1;

inline const int TILE_WIDTH = 32 * scale;
inline const int TILE_HEIGHT = 32 * scale;

inline int corners[4][2] = {{posX + TILE_WIDTH, posY + TILE_WIDTH},
							{posX + TILE_WIDTH, posY + TILE_WIDTH * 23},
							{posX + TILE_WIDTH * 23, posY + TILE_WIDTH * 23},
							{posX + TILE_WIDTH * 23, posY + TILE_WIDTH}};

inline const int TOTAL_TILES = 625;
inline const int TOTAL_TILE_SPRITES = 3;
inline const int ROWS = 25;
inline const int COLS = 25;
inline const int interval = 90;
inline int counter = 0;
inline bool isRandom = false;
inline int lives = 3;

//ghost information
inline SDL_Rect ghost_mBox[4];
inline int ghost_d[4];
inline int ghost_animIdx[4];

//pac-info
inline int pac_d;
inline int pac_animIdx;

//other pac-info
inline SDL_Rect other_pac_box = {0, 0, TILE_WIDTH, TILE_WIDTH};
inline int other_pac_d;
inline int other_pac_animIdx;

inline int dx[4] = {-1, 0, 1, 0};
inline int dy[4] = {0, 1, 0, -1};

inline std::pair<int, int> pac_coor[5][2] = {{{15, 10}, {15, 14}}, {{17, 10}, {17, 14}}, {{15, 9}, {15, 15}}, {{15, 9}, {15, 15}}, {{12, 10}, {12, 14}}};
inline std::pair<int, int> ghost_coor[4] = {{1, 1}, {1, 23}, {23, 23}, {23, 1}};

inline TTF_Font *smallFont = nullptr;
inline TTF_Font *font = nullptr;
inline TTF_Font *largeFont = nullptr;
inline TTF_Font *veryLargeFont = nullptr;
inline TTF_Font *hugeFont = nullptr;

inline SDL_Texture *GRASS = nullptr;
inline SDL_Texture *BRICK = nullptr;
inline SDL_Texture *GRAD1 = nullptr;
inline SDL_Texture *BLACK = nullptr;
inline SDL_Texture *resumeBack = nullptr;
inline SDL_Texture *menuBack = nullptr, *levelsBack = nullptr,
				   *winBack = nullptr, *loseBack = nullptr,
				   *soundBack = nullptr, *quitBack = nullptr,
				   *gameBack = nullptr, *gameBack2 = nullptr, *pausePage = nullptr;

inline SDL_Rect pacBox = {posX + 32, posY + 32, 32, 32};

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
inline int levelScore[5][2] = {0};
inline int totalScore[2] = {0};
inline int lifes[2];
inline int score[2] = {0};

inline int matrix[5][25][25];