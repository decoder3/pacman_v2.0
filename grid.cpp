#include "grid.h"

Grid::Grid()
{
	coin.loadFromFile("Assets/Images/coin.png");
	coinRenderSize = {0, 0, 24, 24};
}

bool Grid::loadTiles(std::string map_path)
{
	// Success flag
	bool tilesLoaded = true;

	// The tile offsets
	int x = posX, y = posY;

	// Open the map
	std::ifstream map(map_path);

	// If the map couldn't be loaded
	if (map.fail())
	{
		printf("Unable to load map file!\n");
		tilesLoaded = false;
	}
	else
	{
		// Initialize the tiles
		for (int i = 0; i < TOTAL_TILES; ++i)
		{
			// Determines what kind of tile will be made
			int tileType = -1;

			// Read tile from map file
			map >> tileType;

			// If the was a problem in reading the map
			if (map.fail())
			{
				// Stop loading map
				printf("Error loading map: Unexpected end of file!\n");
				tilesLoaded = false;
				break;
			}

			// If the number is a valid tile number
			if ((tileType >= 0) && (tileType < TOTAL_TILE_SPRITES))
			{
				tiles[i] = new Tile(x, y, tileType);
			}
			// If we don't recognize the tile type
			else
			{
				// Stop loading map
				printf("Error loading map: Invalid tile type at %d!\n", i);
				tilesLoaded = false;
				break;
			}

			// Move to next tile spot
			x += TILE_WIDTH;

			// If we've gone too far
			if (x - posX >= LEVEL_WIDTH)
			{
				// Move back
				x = posX;

				// Move to the next row
				y += TILE_HEIGHT;
			}
		}
	}

	// Close the file
	map.close();

	// If the map was loaded fine
	return tilesLoaded;
}

void Grid::render()
{
	for (int i = 0; i < TOTAL_TILES; i++)
	{
		// if (tiles[i]->getType() == 1)
		tiles[i]->render();
	}
	int xx = curLevel - 1;
	for (int i = 1; i < 24; i++)
	{
		for (int j = 1; j < 24; j++)
		{
			if (isCoin[xx][i][j])
				coin.render(posX + 32 * j + 4, posY + 32 * i + 4, &coinRenderSize);
		}
	}
}

Grid::~Grid()
{
	for (int i = 0; i < TOTAL_TILES; i++)
	{
		delete tiles[i];
		tiles[i] = nullptr;
	}
}

bool Grid::touchesWall(SDL_Rect box, Tile *tiles[])
{
	for (int i = 0; i < TOTAL_TILES; ++i)
	{
		if (tiles[i]->getType() == 1)
		{
			if (checkCollision(box, tiles[i]->getBox()))
			{
				return true;
			}
		}
	}
	return false;
}
