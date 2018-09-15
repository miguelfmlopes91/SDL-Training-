
#include <SDL.h>
#include <stdio.h>
#include "Game.hpp"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

Game *game = nullptr;

int main(int argc, char *argv[])
{
	game = new Game();
	game->init("Bar da Praia", SCREEN_WIDTH, SCREEN_HEIGHT, false);

	while (game->running())
	{
		game->handleEvents();
		game->update();
		game->render();
	}

	game->clean();
	return 0;
}