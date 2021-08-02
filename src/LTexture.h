#pragma once
#include "head.h"

class LTexture
{
public:
	// Initializes variables
	LTexture();

	// Deallocates memory
	~LTexture();

	// Loads image at specified path
	bool loadFromFile(std::string path);
	bool loadFromFileKey(std::string path, SDL_Color keyColor);

	bool loadFromRenderedText(TTF_Font *font, std::string textureText,
							  SDL_Color textColor);

	// Deallocates texture
	void free();

	// Set color modulation
	void setColor(Uint8 red, Uint8 green, Uint8 blue);

	// Set blending
	void setBlendMode(SDL_BlendMode blending);

	// Set alpha modulation
	void setAlpha(Uint8 alpha);

	SDL_Texture *getTexture();

	// Renders texture at given point
	void render(int x, int y, SDL_Rect *clip = nullptr, double angle = 0.0,
				SDL_Point *center = nullptr,
				SDL_RendererFlip flip = SDL_FLIP_NONE);

	// Gets image dimensions
	int getWidth();
	int getHeight();
	SDL_Texture *mTexture;

private:
	// The actual hardware texture

	// Image dimensions
	int mWidth;
	int mHeight;
};
