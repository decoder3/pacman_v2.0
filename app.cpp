#include "app.h"

bool App::Init()
{

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::cout << "Can't Initialize SDL " << SDL_GetError() << std::endl;
		return false;
	}
	if (TTF_Init() < 0)
	{
		std::cout << "Can't Initialize TTF " << TTF_GetError() << std::endl;
		return false;
	}

	gWindow = SDL_CreateWindow("pacman", winPosX, winPosY, SCREEN_WIDTH, SCREEN_HEIGHT,
							   SDL_WINDOW_SHOWN);
	if (gWindow == NULL)
	{
		std::cout << "Can't Initialize Window " << SDL_GetError() << std::endl;
		return false;
	}

	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
	if (gRenderer == NULL)
	{
		std::cout << "Can't Initialize Renderer " << SDL_GetError() << std::endl;
		return false;
	}

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n",
			   Mix_GetError());
		return false;
	}

	death = Mix_LoadWAV("Assets/sounds/death.wav");
	eatGhost = Mix_LoadWAV("Assets/sounds/eat_ghost.wav");
	eatCoin = Mix_LoadWAV("Assets/sounds/munch.wav");
	pill = Mix_LoadWAV("Assets/sounds/pill.wav");
	start = Mix_LoadWAV("Assets/sounds/game_start.wav");

	GRASS = SDL_CreateTextureFromSurface(gRenderer,
										 IMG_Load("Assets/Images/grass32.jpg"));
	BRICK = SDL_CreateTextureFromSurface(gRenderer,
										 IMG_Load("Assets/Images/brick.jpeg"));
	GRAD1 = SDL_CreateTextureFromSurface(gRenderer,
										 IMG_Load("Assets/Images/grad1.jpg"));

	BLACK = SDL_CreateTextureFromSurface(gRenderer,
										 IMG_Load("Assets/Images/black.jpg"));
	menuBack = SDL_CreateTextureFromSurface(gRenderer,
											IMG_Load("Assets/Images/homepg.png"));
	levelsBack = SDL_CreateTextureFromSurface(
		gRenderer, IMG_Load("Assets/Images/levelspg.png"));
	winBack = SDL_CreateTextureFromSurface(gRenderer,
										   IMG_Load("Assets/Images/winpg.png"));
	loseBack = SDL_CreateTextureFromSurface(gRenderer,
											IMG_Load("Assets/Images/losepg.png"));
	soundBack = SDL_CreateTextureFromSurface(
		gRenderer, IMG_Load("Assets/Images/volumepg.png"));
	quitBack = SDL_CreateTextureFromSurface(gRenderer,
											IMG_Load("Assets/Images/quitpg.png"));
	gameBack = SDL_CreateTextureFromSurface(gRenderer, IMG_Load("Assets/Images/game_back.jpeg"));
	gameBack2 = SDL_CreateTextureFromSurface(gRenderer,
											 IMG_Load("Assets/Images/game_back2.jpeg"));
	resumeBack = SDL_CreateTextureFromSurface(
		gRenderer, IMG_Load("Assets/Images/resumepg.png"));
	resumeBack = SDL_CreateTextureFromSurface(
		gRenderer, IMG_Load("Assets/Images/resumepg.png"));

	smallFont = TTF_OpenFont("Assets/Fonts/cheapmot.ttf", 12);
	font = TTF_OpenFont("Assets/Fonts/cheapmot.ttf", 20);
	largeFont = TTF_OpenFont("Assets/Fonts/cheapmot.ttf", 36);
	veryLargeFont = TTF_OpenFont("Assets/Fonts/cheapmot.ttf", 48);
	hugeFont = TTF_OpenFont("Assets/Fonts/cheapmot.ttf", 96);

	return true;
}

App::~App()
{
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	SDL_DestroyTexture(GRASS);
	SDL_DestroyTexture(BRICK);
	TTF_CloseFont(smallFont);
	TTF_CloseFont(font);
	TTF_CloseFont(largeFont);
	TTF_CloseFont(veryLargeFont);
	TTF_CloseFont(hugeFont);
	Mix_FreeChunk(start);
	Mix_FreeChunk(pill);
	Mix_FreeChunk(eatCoin);
	Mix_FreeChunk(eatGhost);
	Mix_FreeChunk(death);
	start = nullptr;
	pill = nullptr;
	eatGhost = nullptr;
	eatCoin = nullptr;
	death = nullptr;
	Mix_Quit();
}

// void App::pause() { paused = true; }

// void App::resume() { paused = false; }

// void App::toggle() { paused = !paused; }

// bool App::getStatus() { return paused; }

// void App::play() {
//   bool flag = true;
//   while (flag) {
//     SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0xff);
//     SDL_RenderClear(gRenderer);
//     while (SDL_PollEvent(&e) != 0) {
//       if (e.type == SDL_QUIT) {
//         flag = false;
//         break;
//       } else if (e.type == SDL_KEYDOWN) {
//         if (e.key.keysym.sym == SDLK_SPACE) {
//           if (paused) {
//             Mix_PauseMusic();
//           } else {
//           }
//           toggle();
//           break;
//         }
//         player.handleEvent(e);
//       }
//     }
//     if (paused) {
//       player.render();
//     } else {
//       player.animate();
//       player.setPos();
//       player.render();
//     }
//     SDL_RenderPresent(gRenderer);
//     SDL_Delay(100);
//   }
// }

// bool App::loadMedia() {
//   for (int i = 0; i < 20; i++) {
//     for (int j = 0; j < 44; j++) {
//       if (grid[i][j])
//         isCoin[i][j] = false;
//       else
//         isCoin[i][j] = true;
//     }
//   }
//   brick.loadFromFile("Assets/Images/brick.jpeg");
//   grass.loadFromFile("Assets/Images/grass32.jpg");
//   coin.loadFromFile("Assets/Images/coin.png");
//   player.initPlayer();
//   player.setX(posY + 36);
//   player.setY(posX + 36);
//   isCoin[1][1] = false;
// }