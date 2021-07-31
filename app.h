#pragma once
#include "LTexture.h"
#include "head.h"

class App
{
	bool paused = false;

public:
	~App();
	void pause();
	void resume();
	void toggle();
	bool getStatus();
	bool Init();
	void play();
	bool loadMedia();
	void loadFonts();
};