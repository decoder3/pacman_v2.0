#include "app.h"
#include "ghost.h"
#include "grid.h"
#include "head.h"
#include "main_menu.h"
#include "pacman.h"
#include "sounds.h"
using namespace std;

bool mainmenuON = true;
bool levelmenuON = false;
bool soundsettingsON = false;
bool quitoptionON = false; // cross avaliable on the screen
bool gameON = false;
bool pauseON = false;
bool loseON = false;
bool winON = false;

// home page coord
const int powerX = 20, powerY = 20, powerW = 70, powerH = 70;
const int playX = 511, playY = 691, playW = 381, playH = 131;
const int volX = 1221, volY = 802, volW = 150, volH = 150;

// levels page coord
const int levelnoW = 100, levelnoH = 100;
const int level1X = 582, level1Y = 768;
const int level2X = 272, level2Y = 381;
const int level3X = 661, level3Y = 215;
const int level4X = 1184, level4Y = 390;
const int level5X = 1140, level5Y = 71;
const int startX = 1139, startY = 760, startW = 200, startH = 200;
const int levelBackX = 0, levelBackY = 425, lBW = 100, lBH = 150;

// volume page coord
const int MusicX = 145, MusicY = 338;
const int GameX = 145, GameY = 521;
const int optW = 455, optH = 110;
const int backHX = 1177, backHY = 812, backHW = 120, backHH = 120;

// quit page coord
const int QyesX = 250 + 77, QYesY = 200 + 417, QNoX = 250 + 575,
		  QNoY = 200 + 417;
const int QoptW = 270, QoptH = 100;

// game page
const int pauseX = 640, pauseY = 0, pauseW = 100, pauseH = 100;

// pause page
const int resumeX = 250 + 222, resumeY = 200 + 145, resumeW = 450,
		  resumeH = 100;
const int RbackhomeX = 250 + 83, RbackhomeY = 200 + 423, RHomeW = 200,
		  RHomeH = 200;
const int RreplayX = 250 + 361, RreplayY = 200 + 453, RreplayW = 50,
		  RreplayH = 230;
const int RvolX = 250 + 750, RVolY = 200 + 437, RvolW = 170, RvolH = 170;

// winlose page coord
const int homeLX = 250 + 63, homeLY = 200 + 452, homeLdim = 200;
const int replayX = 250 + 648, replayY = 200 + 496, replayW = 240, replayH = 50;

SDL_Rect selected;

void togglePause()
{
	pauseON = !pauseON;
	if (pauseON)
	{
		Sounds::getInstance()->pauseAll();
	}
	else
	{
		Sounds::getInstance()->resumeAll();
	}
}

bool interfaceHandleevent(SDL_Event &e, bool flag)
{
	if (e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN ||
		e.type == SDL_MOUSEBUTTONUP)
	{
		// Get mouse position
		int x, y;
		SDL_GetMouseState(&x, &y);
		// Check if mouse is in button
		bool powerb = false, playb = false, volumeb = false;
		bool level1b = false, level2b = false, level3b = false, level4b = false,
			 level5b = false;
		bool startb = false, lBack = false;
		bool pauseB = false;
		bool musicb = false, gameb = false;
		bool backtohomeb = false;
		bool QuitYesb = false, QuitNOb = false;
		bool gobacktohomeb = false;
		bool replayb = false;
		bool Rresumeb = false, Rreplayb = false, RhomeB = false, Rvolb = false;
		if (powerX <= x && x <= powerX + powerW && powerY <= y &&
			y <= powerY + powerH)
			powerb = true;
		if (playX <= x && x <= playX + playW && playY <= y && y <= playY + playH)
			playb = true;
		if (volX <= x && x <= volX + volW && volY <= y && y <= volY + volH)
			volumeb = true;
		if (level1X <= x && x <= level1X + levelnoW && level1Y <= y &&
			y <= level1Y + levelnoH)
			level1b = true;
		if (level2X <= x && x <= level2X + levelnoW && level2Y <= y &&
			y <= level2Y + levelnoH)
			level2b = true;
		if (level3X <= x && x <= level3X + levelnoW && level3Y <= y &&
			y <= level3Y + levelnoH)
			level3b = true;
		if (level4X <= x && x <= level4X + levelnoW && level4Y <= y &&
			y <= level4Y + levelnoH)
			level4b = true;
		if (level5X <= x && x <= level5X + levelnoW && level5Y <= y &&
			y <= level5Y + levelnoH)
			level5b = true;
		if (startX <= x && x <= startX + startW && startY <= y &&
			y <= startY + startH)
			startb = true;
		if (levelBackX <= x && x <= levelBackX + lBW && levelBackY <= y &&
			y <= levelBackY + lBH)
			lBack = true;
		if (pauseX <= x && x <= pauseX + pauseW && pauseY <= y &&
			y <= pauseY + pauseH)
			pauseB = true;
		if (MusicX <= x && x <= MusicX + optW && MusicY <= y && y <= MusicY + optH)
			musicb = true;
		if (GameX <= x && x <= GameX + optW && GameY <= y && y <= GameY + optH)
			gameb = true;
		if (backHX <= x && x <= backHX + backHW && backHY <= y &&
			y <= backHY + backHH)
			backtohomeb = true;
		if (QyesX <= x && x <= QyesX + QoptW && QYesY <= y && y <= QYesY + QoptH)
			QuitYesb = true;
		if (QNoX <= x && x <= QNoX + QoptW && QNoY <= y && y <= QNoY + QoptH)
			QuitNOb = true;
		if (homeLX <= x && x <= homeLX + homeLdim && homeLY <= y &&
			y <= homeLY + homeLdim)
			gobacktohomeb = true;
		if (replayX <= x && x <= replayX + replayW && replayY <= y &&
			y <= replayY + replayH)
			replayb = true;

		if (resumeX <= x && x <= resumeX + resumeW && resumeY <= y &&
			y <= resumeY + resumeH)
			Rresumeb = true;
		if (RreplayX <= x && x <= RreplayX + RreplayW && RreplayY <= y &&
			y <= RreplayY + RreplayH)
			Rreplayb = true;
		if (RbackhomeX <= x && x <= RbackhomeX + RHomeW && RbackhomeY <= y &&
			y <= RbackhomeY + RHomeH)
			RhomeB = true;
		if (RvolX <= x && x <= RvolX + RvolW && RVolY <= y && y <= RVolY + RvolH)
			Rvolb = true;

		// one problem: on any page if we get on to some value area then flags will
		// be true, means on menu page level flags can go true this is a problem, no
		// such problem coz in main we are taking pages as per flags and in each
		// iter these flags update to false
		if (mainmenuON && playb && e.type == SDL_MOUSEBUTTONDOWN)
		{
			mainmenuON = false;
			levelmenuON = true;
		}
		if (mainmenuON && powerb && e.type == SDL_MOUSEBUTTONDOWN)
		{
			mainmenuON = false;
			quitoptionON = true;
		}
		if (quitoptionON && QuitYesb && e.type == SDL_MOUSEBUTTONDOWN)
		{
			mainmenuON = true;
			quitoptionON = false;
			flag = false;
		}
		if (quitoptionON && QuitNOb && e.type == SDL_MOUSEBUTTONDOWN)
		{
			mainmenuON = true;
			quitoptionON = false;
		}
		if (mainmenuON && volumeb && e.type == SDL_MOUSEBUTTONDOWN)
		{
			mainmenuON = false;
			soundsettingsON = true;
		}

		if (soundsettingsON && backtohomeb && e.type == SDL_MOUSEBUTTONDOWN)
		{
			soundsettingsON = false;
			mainmenuON = true;
		}
		if (levelmenuON && level1b && e.type == SDL_MOUSEBUTTONDOWN)
		{
			curLevel = 1;
		}
		if (levelmenuON && level2b && e.type == SDL_MOUSEBUTTONDOWN)
		{
			curLevel = 2;
		}
		if (levelmenuON && level3b && e.type == SDL_MOUSEBUTTONDOWN)
		{
			curLevel = 3;
		}
		if (levelmenuON && level4b && e.type == SDL_MOUSEBUTTONDOWN)
		{
			curLevel = 4;
		}
		if (levelmenuON && level5b && e.type == SDL_MOUSEBUTTONDOWN)
		{
			curLevel = 5;
		}
		if (levelmenuON && startb && e.type == SDL_MOUSEBUTTONDOWN)
		{
			levelmenuON = false;
			gameON = true;
			int xx = curLevel - 1;
			totalCoins[xx] = 0;
			string matrix_path = "Assets/levels/level";
			char c = curLevel + '0';
			matrix_path += c;
			matrix_path += ".map";
			ifstream ss;
			ss.open(matrix_path);
			for (int i = 0; i < 25; i++)
			{
				for (int j = 0; j < 25; j++)
				{
					int x;
					ss >> x;
					matrix[xx][i][j] = x;
					if (!matrix[xx][i][j])
					{
						isCoin[xx][i][j] = true;
						totalCoins[xx]++;
					}
					else
						isCoin[xx][i][j] = false;
				}
			}
			isCoin[xx][pac_coor[xx].first][pac_coor[xx].second] = false;
			totalCoins[xx]--;
			first_time = true;
		}
		if (levelmenuON && lBack && e.type == SDL_MOUSEBUTTONDOWN)
		{
			levelmenuON = false;
			mainmenuON = true;
		}

		if (gameON && pauseB && e.type == SDL_MOUSEBUTTONDOWN)
		{
			gameON = false;
			togglePause();
		}
		else if (pauseON && pauseB && e.type == SDL_MOUSEBUTTONDOWN)
		{
			gameON = true;
			togglePause();
		}

		if ((winON || loseON) && gobacktohomeb && e.type == SDL_MOUSEBUTTONDOWN)
		{
			winON = false;
			loseON = false;
			mainmenuON = true;
		}
		if ((winON || loseON) && replayb && e.type == SDL_MOUSEBUTTONDOWN)
		{
			winON = false;
			loseON = false;
			levelmenuON = true;
		}

		if (pauseON && Rresumeb && e.type == SDL_MOUSEBUTTONDOWN)
		{
			togglePause();
			gameON = true;
		}
		if (pauseON && RhomeB && e.type == SDL_MOUSEBUTTONDOWN)
		{
			pauseON = false;
			mainmenuON = true;
		}
		if (pauseON && Rvolb && e.type == SDL_MOUSEBUTTONDOWN)
		{
			pauseON = false;
			soundsettingsON = true;
		}
		if (pauseON && Rreplayb && e.type == SDL_MOUSEBUTTONDOWN)
		{
			pauseON = false;
			levelmenuON = true;
		}
	}
	else if (e.type == SDL_KEYDOWN)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_s:
			Sounds::getInstance()->toggleEnabled();
			break;
		case SDLK_m:
			Sounds::getInstance()->toggleMusicEnabled();
			Sounds::getInstance()->playNormalMusic();
			break;
		case SDLK_p:
			togglePause();
		case SDLK_SPACE:
			if (gameON)
			{
				gameON = false;
				togglePause();
			}
			else if (pauseON)
			{
				gameON = true;
				togglePause();
			}
		}
	}
	return (flag);
}

int main()
{
	App app;
	app.Init();
	bool flag = true;
	Grid grid;
	Pacman pacman;
	Ghost ghost;
	SDL_Rect smallmenu;
	smallmenu.x = 250;
	smallmenu.y = 200;
	smallmenu.w = 900;
	smallmenu.h = 600;
	std::cout << pacBox.x << "-" << pacBox.y << std::endl;
	SDL_Event e;
	while (flag)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				flag = false;
				break;
			}
			flag = interfaceHandleevent(e, flag);
			if (gameON)
			{
				pacman.handleEvent(e);
			}
		}
		if (lifes == 0)
		{
			gameON = false;
			loseON = true;
		}
		if (score == totalCoins[curLevel - 1])
		{
			gameON = false;
			winON = true;
			ghost.reset();
			pacman.reset();
			curLevel = curLevel + 1;
			if (curLevel == 6)
				curLevel = 1;
		}
		if (gameON)
		{
			SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0xff);
			SDL_RenderClear(gRenderer);
			SDL_RenderCopy(gRenderer, gameBack, NULL, NULL);
			if (first_time)
			{
				first_time = false;
				score = 0;
				grid.loadTiles("Assets/levels/level" + to_string(curLevel) + ".map");
				lifes = 3;
				SDL_RenderCopy(gRenderer, gameBack, NULL, NULL);
				grid.render();
				pacman.render();
				SDL_RenderPresent(gRenderer);
				ghost.render();
				Sounds::getInstance()->playIntro();
				SDL_Delay(4500);
				Sounds::getInstance()->playNormalMusic();
			}
			//

			SDL_Color blue = {255, 255, 255};
			string scor = to_string(score);
			string life = "X" + to_string(lifes);
			char *sco = const_cast<char *>(scor.c_str());
			char *lif = const_cast<char *>(life.c_str());

			SDL_Surface *surfaceMessage =
				TTF_RenderText_Solid(font, sco, blue);
			SDL_Surface *surfaceMessage2 =
				TTF_RenderText_Solid(font, lif, blue);
			SDL_Texture *Message = SDL_CreateTextureFromSurface(gRenderer, surfaceMessage);
			SDL_Texture *Message2 = SDL_CreateTextureFromSurface(gRenderer, surfaceMessage2);
			SDL_Rect masrec = {256, 12, scor.length() * 50, 73 - 12};
			SDL_Rect masrec2 = {1190, 102, life.length() * 50, 175 - 102};
			SDL_RenderCopy(gRenderer, Message, NULL, &masrec);
			SDL_RenderCopy(gRenderer, Message2, NULL, &masrec2);
			//

			int x = ghost.checkCollissionWithPacman();
			pacman.eat();
			if (x != -1)
			{
				pacman.death();
				// ghost.pacDeath(x);
				grid.render();
				pacman.render();
				ghost.render();
				Sounds::getInstance()->playSingleSound(Sounds::DYING);
				// Mix_PlayChannel(-1, death, 0.5);
				SDL_Delay(1500);
				counter = 0;
				ghost.reset();
				pacman.reset();
			}
			pacman.move(grid.tiles);
			pacman.animate();
			ghost.move(grid.tiles);
			ghost.animate();
			grid.render();
			pacman.render();
			ghost.render();
		}
		else if (mainmenuON)
		{
			SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0xff);
			SDL_RenderClear(gRenderer);
			SDL_RenderCopy(gRenderer, menuBack, NULL, NULL);
			lifes = 3;
		}
		else if (levelmenuON)
		{
			SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0xff);
			SDL_RenderClear(gRenderer);
			pacman.reset();
			SDL_RenderCopy(gRenderer, levelsBack, NULL, NULL);
		}
		else if (soundsettingsON)
		{
			SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0xff);
			SDL_RenderClear(gRenderer);
			SDL_RenderCopy(gRenderer, soundBack, NULL, NULL);
		}
		else if (quitoptionON)
		{
			SDL_RenderCopy(gRenderer, quitBack, NULL, &smallmenu);
		}
		else if (pauseON)
		{
			SDL_RenderCopy(gRenderer, resumeBack, NULL, &smallmenu);
		}
		else if (winON)
		{
			SDL_RenderCopy(gRenderer, winBack, NULL, &smallmenu);
			lifes = 3;
		}
		else if (loseON)
		{
			SDL_RenderCopy(gRenderer, loseBack, NULL, &smallmenu);
			lifes = 3;
		}
		SDL_RenderPresent(gRenderer);
		SDL_Delay(50);
	}
}