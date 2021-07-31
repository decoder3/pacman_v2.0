#include "Tile.h"
#include "grid.h"
#include "head.h"

class Ghost
{
	LTexture sprites[4][4][2];
	int state[4];
	int dir[4];
	bool checkIfDirectionSet[4];
	LTexture cur[4];
	SDL_Rect renderSize;
	int GHOST_VEL;

	int nextDir[4];

public:
	Ghost();
	int checkCollissionWithPacman();
	static const int G_WIDTH = 35;
	static const int G_HEIGHT = 35;
	void handleEvent(SDL_Event &e);
	void move(Tile *tiles[]);
	void changeDir(int idx, Tile *tiles[]);
	void findDir(int i);
	void animate();
	void init();
	void render();
	void reset();
	void pacDeath(int x);
	std::vector<int> checkDirections(int i, Tile *tiles[]);
	void findRandomDir(int idx, Tile *tiles[]);
};