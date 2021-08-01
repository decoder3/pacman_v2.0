#include "server.h"
#include "client.h"
#include "app.h"
#include "ghost.h"
#include "grid.h"
#include "head.h"
#include "main_menu.h"
#include "pacman.h"
#include "sounds.h"
using namespace std;
mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());

LTexture pl[4], pd[4], pr[4], pu[4];
int pacRenderSz = 24 * scale;
SDL_Rect pacRenderRect = {0, 0, pacRenderSz, pacRenderSz};

int mainIdx = 0;
bool gameOn = false;
bool gamePause = false;
bool firstTime = false;
SDL_Rect winBox = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};

LTexture mainPage[4];
LTexture modePage[2];

int socket_;

enum pages
{
	MAIN,
	MODE,
	INSTRUCTIONS,
	GAME
};

int curPage = MAIN;

void initMain()
{

	for (int i = 0; i < 4; i++)
	{
		string imgPath = "Assets/Images/main";
		char c = i + '0';
		imgPath += c;
		imgPath += ".jpg";
		mainPage[i].loadFromFile(imgPath);
	}
}

void render_other_player()
{
	int x = other_pac_d;
	LTexture cur_texture;
	switch (x)
	{
	case 0:
		cur_texture = pl[other_pac_animIdx];
		break;
	case 1:
		cur_texture = pd[other_pac_animIdx];
		break;
	case 2:
		cur_texture = pr[other_pac_animIdx];
		break;
	case 3:
		cur_texture = pu[other_pac_animIdx];
		break;
	default:
		break;
	}
	cout << other_pac_box.x << " " << other_pac_box.y << " " << other_pac_d << " " << other_pac_animIdx << endl;
	other_pac_animIdx = (other_pac_animIdx + 1) % 4;
	cur_texture.render(other_pac_box.x + TILE_WIDTH / 8, other_pac_box.y + TILE_WIDTH / 8, &pacRenderRect);
}

void other_pac_reset()
{
	// int idx = connection_state == "server" ? 1 : 0;
	// int X = TILE_WIDTH * pac_coor[curLevel - 1][idx].first;
	// int Y = TILE_WIDTH * pac_coor[curLevel - 1][idx].second;
	// other_pac_box = {posX + X, posY + Y, TILE_WIDTH, TILE_WIDTH};
	// other_pac_d = idx ? 2 : 0;
	// other_pac_animIdx = 0;
}

void initMode()
{
	for (int i = 0; i < 2; i++)
	{
		string imgPath = "Assets/levels/level";
		char c = (i + 1) + '0';
		imgPath += c;
		imgPath += ".jpg";
		modePage[i].loadFromFile(imgPath);
	}
}

void initLevel(int idx)
{
	totalCoins[idx] = 0;
	string matrix_path = "Assets/levels/level";
	char c = '0' + (idx + 1);
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
			matrix[idx][i][j] = x;
			if (matrix[idx][i][j] == 2)
			{
				isCoin[idx][i][j] = true;
				totalCoins[idx]++;
			}
			else
				isCoin[idx][i][j] = false;
		}
	}
	firstTime = true;
}

void initGame()
{

	if (modeIdx == 1)
	{
		if (connection_state == "server")
		{
			socket_ = start_server();
		}
		else if (connection_state == "client")
		{
			cout << "Trying to connect ... " << endl;
			socket_ = connect_client();
		}
		else
		{
			cout << "Invalid Argument" << endl;
			exit(-1);
		}
		if (connection_state == "server")
		{
			send_from_server("hey_there", socket_);
			string xyz = receive_in_server(socket_);
			cout << xyz << endl;
		}
		else
		{
			send_from_client("hello_server", socket_);
			string abc = receive_in_client(socket_);
			cout << abc << endl;
		}
	}
	lifes[0] = lifes[1] = 10;
	score[0] = score[1] = 0;
	gameOn = true;
	curLevel = 1;
	initLevel(0);
	pl[0].loadFromFile("Assets/Images/pac_left1.png");
	pl[1].loadFromFile("Assets/Images/pac_left2.png");
	pl[2].loadFromFile("Assets/Images/pac_left1.png");
	pl[3].loadFromFile("Assets/Images/pacman.png");
	pr[0].loadFromFile("Assets/Images/pac_right1.png");
	pr[1].loadFromFile("Assets/Images/pac_right2.png");
	pr[2].loadFromFile("Assets/Images/pac_right1.png");
	pr[3].loadFromFile("Assets/Images/pacman.png");
	pu[0].loadFromFile("Assets/Images/pac_up1.png");
	pu[1].loadFromFile("Assets/Images/pac_up2.png");
	pu[2].loadFromFile("Assets/Images/pac_up1.png");
	pu[3].loadFromFile("Assets/Images/pacman.png");
	pd[0].loadFromFile("Assets/Images/pac_down1.png");
	pd[1].loadFromFile("Assets/Images/pac_down2.png");
	pd[2].loadFromFile("Assets/Images/pac_down1.png");
	pd[3].loadFromFile("Assets/Images/pacman.png");
}

void togglePause()
{
	gamePause = !gamePause;
	if (pause)
	{
		Sounds::getInstance()->pauseAll();
	}
	else
	{
		Sounds::getInstance()->resumeAll();
	}
}

void handleEvent(SDL_Event &e)
{
	if (e.type == SDL_KEYDOWN)
	{
		if (curPage == MAIN)
		{
			switch (e.key.keysym.sym)
			{
			case SDLK_RETURN:
				curPage = MODE;
				break;
			case SDLK_i:
				curPage = INSTRUCTIONS;
				break;
			case SDLK_ESCAPE:
				exit(0);
				break;
			default:
				break;
			}
		}
		else if (curPage == MODE)
		{
			switch (e.key.keysym.sym)
			{
			case SDLK_UP:
				modeIdx = (modeIdx + 1) % 2;
				break;
			case SDLK_DOWN:
				modeIdx = (modeIdx + 1) % 2;
				break;
			case SDLK_RETURN:
				curPage = GAME;
				initGame();
				break;
			case SDLK_BACKSPACE:
				curPage = MAIN;
				break;
			default:
				break;
			}
		}
		else if (curLevel == GAME)
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
			case SDLK_SPACE:
				togglePause();
			default:
				break;
			}
		}
	}
}

int main(int argc, char *argv[])
{
	connection_state = argv[1];
	App app;
	app.Init();
	initMain();
	initMode();
	Grid grid;
	Pacman pacman;
	Ghost ghost;

	SDL_Rect smallmenu;
	smallmenu.x = 250;
	smallmenu.y = 200;
	smallmenu.w = 900;
	smallmenu.h = 600;

	SDL_Event e;
	bool flag = true;
	while (flag)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				flag = false;
				break;
			}
			handleEvent(e);
			if (gameOn)
				pacman.handleEvent(e);
		}
		if (!flag)
			break;
		SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0xff);
		SDL_RenderClear(gRenderer);
		if (gameOn)
		{
			if (modeIdx == 0)
			{

				SDL_RenderCopy(gRenderer, gameBack, NULL, NULL);
				if (firstTime)
				{
					levelScore[curLevel - 1][0] = levelScore[curLevel - 1][1] = 0;
					grid.loadTiles("Assets/levels/level" + to_string(curLevel) + ".map");
					grid.render();
					pacman.render();
					ghost.render();
					SDL_RenderPresent(gRenderer);
					Sounds::getInstance()->playIntro();
					SDL_Delay(4500);
					Sounds::getInstance()->playNormalMusic();
					firstTime = false;
				}
				else
				{
					string scor = to_string(score[0]);
					string life = "X" + to_string(lifes[0]);
					char *sco = const_cast<char *>(scor.c_str());
					char *lif = const_cast<char *>(life.c_str());
					SDL_Surface *surfaceMessage =
						TTF_RenderText_Solid(font, sco, WHITE_COLOR);
					SDL_Surface *surfaceMessage2 =
						TTF_RenderText_Solid(font, lif, WHITE_COLOR);
					SDL_Texture *Message = SDL_CreateTextureFromSurface(gRenderer, surfaceMessage);
					SDL_Texture *Message2 = SDL_CreateTextureFromSurface(gRenderer, surfaceMessage2);
					SDL_Rect masrec = {184, 22, scor.length() * 20, 40};
					SDL_Rect masrec2 = {1133, 88, life.length() * 20, 40};
					SDL_RenderCopy(gRenderer, Message, NULL, &masrec);
					SDL_RenderCopy(gRenderer, Message2, NULL, &masrec2);

					int x = ghost.checkCollissionWithPacman(pacBox);
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
						grid.render();
						pacman.render();
						ghost.render();
					}
					else
					{
						pacman.eat(0);
						pacman.move(grid.tiles);
						pacman.animate();
						ghost.move(grid.tiles);
						ghost.animate();
						grid.render();
						pacman.render();
						ghost.render();
					}
					//TODO:: insert a page over here!
					if (lifes[0] == 0)
						exit(0);
					if (levelScore[curLevel - 1][0] + levelScore[curLevel - 1][1] == totalCoins[curLevel - 1])
					{
						curLevel++;
						if (curLevel == 6)
							curLevel = 1;
						initLevel(curLevel - 1);
						ghost.reset();
						pacman.reset();
					}
				}
			}
			else
			{
				if (connection_state == "server")
				{
					string s;
					for (int i = 0; i < 4; i++)
					{
						s = s + to_string(ghost_mBox[i].x) + "," + to_string(ghost_mBox[i].y) + "," + to_string(ghost_d[i]) + "," + to_string(ghost_animIdx[i]) + ",";
					}
					s += to_string(pacBox.x) + "," + to_string(pacBox.y) + "," + to_string(pac_d) + "," + to_string(pac_animIdx) + ",";
					s += to_string(score[0]);
					send_from_server(s, socket_);
					string dump = receive_in_server(socket_);
					vector<string> v;
					stringstream ss(dump);
					while (ss.good())
					{
						string substr;
						getline(ss, substr, ',');
						v.push_back(substr);
					}
					if (v.size() != 5)
					{
						cout << "size not matching from client information" << endl;
						cout << "probably client disconnected" << endl;
						// exit(0);
						// game_count_ = 0;
						// blink_count_ = 0;
						// game_state_ = game_state::gameover;
						// disconnected = true;
					}
					else
					{
						other_pac_box.x = stoi(v[0]);
						other_pac_box.y = stoi(v[1]);
						other_pac_d = stoi(v[2]);
						other_pac_animIdx = stoi(v[3]);
						score[1] = stoi(v[4]);
					}
				}
				else
				{
					string s = to_string(pacBox.x) + "," + to_string(pacBox.y) + "," + to_string(pac_d) + "," + to_string(pac_animIdx) + ",";
					s += to_string(score[0]);
					send_from_client(s, socket_);
					string in = receive_in_client(socket_);
					vector<string> v;
					stringstream ss(in);
					while (ss.good())
					{
						string substr;
						getline(ss, substr, ',');
						v.push_back(substr);
					}
					if (v.size() != 21)
					{
						cout << "size not matching from server information" << endl;
						cout << "probably server disconnected" << endl;
						// exit(0);
						// game_count_ = 0;
						// blink_count_ = 0;
						// game_state_ = game_state::gameover;
						// disconnected = true;
					}
					else
					{
						int i = 0;
						for (int j = 0; j < 4; j++)
						{
							ghost_mBox[j].x = stoi(v[i++]);
							ghost_mBox[j].y = stoi(v[i++]);
							ghost_d[j] = stoi(v[i++]);
							ghost_animIdx[j] = stoi(v[i++]);
						}
						other_pac_box.x = stoi(v[i++]);
						other_pac_box.y = stoi(v[i++]);
						other_pac_d = stoi(v[i++]);
						other_pac_animIdx = stoi(v[i++]);
						score[1] = stoi(v[i++]);
					}
				}

				// start rendering...
				SDL_RenderCopy(gRenderer, gameBack2, NULL, NULL);
				if (firstTime)
				{
					levelScore[curLevel - 1][0] = levelScore[curLevel - 1][1] = 0;
					grid.loadTiles("Assets/levels/level" + to_string(curLevel) + ".map");
					grid.render();
					pacman.render();
					render_other_player();
					ghost.render();
				}
				else
				{
					LTexture score1, score2, life1, life2;
					score1.loadFromRenderedText(font, to_string(score[0]), WHITE_COLOR);
					score2.loadFromRenderedText(font, to_string(score[1]), WHITE_COLOR);
					life1.loadFromRenderedText(font, "X" + to_string(lifes[0]), WHITE_COLOR);
					life2.loadFromRenderedText(font, "X" + to_string(lifes[1]), WHITE_COLOR);
					SDL_Rect score1_rect, score2_rect, life1_rect, life2_rect;
					score1_rect = {159, 50, (int)(to_string(score[0]).size()) * 20, 30};
					score2_rect = {1173, 50, (int)(to_string(score[1]).size()) * 20, 30};
					life1_rect = {160, 90, 40, 30};
					life2_rect = {1180, 90, 40, 30};
					score1.render(score1_rect.x, score1_rect.y, &score1_rect);
					score2.render(score2_rect.x, score2_rect.y, &score2_rect);
					life1.render(life1_rect.x, life1_rect.y, &life1_rect);
					life2.render(life2_rect.x, life2_rect.y, &life2_rect);

					if (connection_state == "server")
					{
						int x = ghost.checkCollissionWithPacman(pacBox);
						// int y = ghost.checkCollissionWithPacman(other_pac_box);
						if (x != -1)
						{
							pacman.death();
							grid.render();
							ghost.render();
							pacman.render();
							// render_other_player();
							pl[0].render(other_pac_box.x + TILE_WIDTH / 8, other_pac_box.y + TILE_WIDTH / 8, &pacRenderRect);
							Sounds::getInstance()->playSingleSound(Sounds::DYING);
							SDL_Delay(1500);
							counter = 0;
							ghost.reset();
							pacman.reset();
						}
						// else if (y != -1)
						// {
						// 	grid.render();
						// 	pacman.render();
						// 	render_other_player();
						// 	ghost.render();
						// 	counter = 0;
						// 	ghost.reset();
						// 	lifes[1]--;
						// 	// other_pac_die();
						// }
						else
						{
							int rrxx = rng() % 2;
							pacman.eat(rrxx);
							pacman.eat(rrxx ^ 1);
							pacman.move(grid.tiles);
							pacman.animate();
							ghost.move(grid.tiles);
							ghost.animate();
							grid.render();
							ghost.render();
							pacman.render();
							// render_other_player();
							pl[0].render(other_pac_box.x + TILE_WIDTH / 8, other_pac_box.y + TILE_WIDTH / 8, &pacRenderRect);
						}

						//TODO:: insert a page over here!
						if (lifes[0] == 0)
							exit(0);
						if (levelScore[curLevel - 1][0] + levelScore[curLevel - 1][1] == totalCoins[curLevel - 1])
						{
							curLevel++;
							if (curLevel == 6)
								curLevel = 1;
							initLevel(curLevel - 1);
							ghost.reset();
							pacman.reset();
						}
					}
					else
					{
						int x = ghost.checkCollissionWithPacman(pacBox);
						// int y = ghost.checkCollissionWithPacman(other_pac_box);
						if (x != -1)
						{
							pacman.death();
							grid.render();
							pacman.render();
							ghost.render();
							// render_other_player();
							pl[0].render(other_pac_box.x + TILE_WIDTH / 8, other_pac_box.y + TILE_WIDTH / 8, &pacRenderRect);
							Sounds::getInstance()->playSingleSound(Sounds::DYING);
							SDL_Delay(1500);
							counter = 0;
							ghost.reset();
							pacman.reset();
						}
						// else if (y != -1)
						// {
						// }
						else
						{
							int rrxx = rng() % 2;
							pacman.eat(rrxx);
							pacman.eat(rrxx ^ 1);

							pacman.move(grid.tiles);
							pacman.animate();
							// ghost.move(grid.tiles);
							// ghost.animate();
							grid.render();
							ghost.render();
							pacman.render();
							// render_other_player();
							pl[0].render(other_pac_box.x + TILE_WIDTH / 8, other_pac_box.y + TILE_WIDTH / 8, &pacRenderRect);
						}
						if (lifes[0] == 0)
							exit(0);
						if (levelScore[curLevel - 1][0] + levelScore[curLevel - 1][1] == totalCoins[curLevel - 1])
						{
							curLevel++;
							if (curLevel == 6)
								curLevel = 1;
							initLevel(curLevel - 1);
							ghost.reset();
							pacman.reset();
						}
					}
				}
			}
		}
		else if (curPage == MAIN)
		{
			mainPage[mainIdx].render(0, 0, &winBox);
			mainIdx = (mainIdx + 1) % 4;
			SDL_Delay(500);
		}
		else if (curPage == MODE)
		{
			modePage[modeIdx].render(0, 0, &winBox);
		}
		SDL_RenderPresent(gRenderer);
		if (firstTime)
		{
			Sounds::getInstance()->playIntro();
			SDL_Delay(4500);
			Sounds::getInstance()->playNormalMusic();
			firstTime = false;
		}
		SDL_Delay(45);
	}
}