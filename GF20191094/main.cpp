#include "Game.h"
#include<iostream>
//Game* g_game = 0;

int main(int argc, char* argv[])
{
	/*g_game = new Game();
	g_game->init("Chapter 1", 100, 100, 640, 480, 0);
	while (g_game->running())
	{
		g_game->handleEvents();
		g_game->update();
		g_game->render();
		SDL_Delay(10);
	}
	g_game->clean();*/
	const int FPS = 60;
	const int DELAY_TIME = 1000.0f / FPS;
	if (TheGame::Instance()->init("Chapter 1", 100, 100, 800, 480, false)) {
		Uint32 frameStart, frameTime;
		while (TheGame::Instance()->running()) {
			frameStart = SDL_GetTicks();
			TheGame::Instance()->handleEvents();
			TheGame::Instance()->update();
			TheGame::Instance()->render();
			frameTime = SDL_GetTicks() - frameStart;
			if (frameTime < DELAY_TIME) {
				SDL_Delay((int)(DELAY_TIME - frameTime));
			}
		}
	}
	TheGame::Instance()->clean();
	return 0;
}