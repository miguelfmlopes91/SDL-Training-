
#include <SDL.h>
#include <stdio.h>
#include "Game.hpp"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define FPS 60

Game *game = nullptr;

int main(int argc, char *argv[])
{

	const int frameDelay = (1000 / FPS);
	Uint32 frameStart;
	int frameTime;

	game = new Game();
	game->init("Bar da Praia", SCREEN_WIDTH, SCREEN_HEIGHT, false);

	while (game->running())
	{
		frameStart = SDL_GetTicks(); //how many miliseconds has been since SDL has been initialized

		game->handleEvents();
		game->update();
		game->render();

		frameTime = SDL_GetTicks() - frameStart; //how many time in miliseconds it takes to go trhough the whole loop
		if (frameDelay>frameTime) //if there's frame delay, we need to delay
		{
			SDL_Delay(frameDelay - frameTime);
		}
	}

	game->clean();
	return 0;
}