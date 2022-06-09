#include <SDL2/SDL.h>
#include <iostream>
#include "../include/headers/Game.h"

#define FPS 60
#define DELAY_TIME (1000.0 / FPS)

int main(int argc, char* args[])
{
	Uint32 frameStart, frameTime;

	// initialize SDL
	if (TheGame::Instance() -> init("Chapter 1", 100, 100, 640, 480, 0))
	{
		std::cout <<"game init success\n";

		while (TheGame::Instance() -> running())
		{
			frameStart = SDL_GetTicks64();

			TheGame::Instance() -> handleEvents();
			TheGame::Instance() -> update();
			TheGame::Instance() -> render();

			frameTime = SDL_GetTicks64() - frameStart;

			if (frameTime < DELAY_TIME)
			{
				SDL_Delay(static_cast<int>(DELAY_TIME - frameTime));
			}
		}
	}
	else
	{
		std::cout <<"game init failure - " << SDL_GetError() << "\n";
	}

	std::cout << "game closing...\n";
	TheGame::Instance() -> clean();

	return 0;
}