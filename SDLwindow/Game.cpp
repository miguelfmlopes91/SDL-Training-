#include "Game.hpp"
#include "TextureManager.hpp"
#include "Map.hpp"
#include "ECS/ECS.hpp"
#include "ECS/Components.hpp"
#include "Vector2D.hpp"
#include "ECS\KeyboardController.hpp"
#include "Collision.hpp"

Map* map;
Manager manager;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

std::vector<ColliderComponent*> Game::colliders;

bool Game::isRunning = false;

auto& player(manager.addEntity());
auto& wall(manager.addEntity());

const char* mapfile = "Resources/terrain_ss.png";

enum groupLabels : std::size_t
{
	groupMap,
	groupPlayers,
	groupEnemies,
	groupColliders
};

auto& tiles(manager.getGroup(groupMap));
auto& players(manager.getGroup(groupPlayers));
auto& enemies(manager.getGroup(groupEnemies));

Game::Game()
{}

Game::~Game()
{}

void Game::init(const char* title, int width, int height, bool fullscreen)
{
	int flags = 0;

	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		}

		isRunning = true;
	}

	map = new Map();

	Map::LoadMap("Resources/map.map", 25, 20);


	player.addComponent<TransformComponent>(4);
	player.addComponent<SpriteComponent>("Resources/player_anims.png",true);
	player.addComponent<KeyboardController>();
	player.addComponent<ColliderComponent>("player");
	player.addGroup(groupPlayers);

}

void Game::handleEvents()
{


	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;
	default:
		break;
	}
}

void Game::update()
{
	manager.refresh();
	manager.update();

	Vector2D pVel = player.getComponent<TransformComponent>().velocity;
	int pSpeed = player.getComponent<TransformComponent>().speed;

	//for (auto cc: colliders)
	//{
	//	Collision::AABB(player.getComponent<ColliderComponent>(), *cc);
	//}
	for each (auto t in tiles)
	{
		t->getComponent<TileComponent>().destRect.x += -(pVel.x * pSpeed);
		t->getComponent<TileComponent>().destRect.y += -(pVel.y * pSpeed);

	}
}


void Game::render()
{
	SDL_RenderClear(renderer);
	//add all textures to be rendered

	for each (auto& t in tiles)
	//draw each tile one after another
	{
		t->draw();
	}
	for each (auto& p in players)
	{
		p->draw();
	}
	for each (auto& e in enemies)
	{
		e->draw();
	}

	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}

void Game::AddTile(int srcX, int srcY, int xPos, int yPos)
{
	auto& tile(manager.addEntity());
	tile.addComponent<TileComponent>(srcX, srcY, xPos, yPos, mapfile);
	tile.addGroup(groupMap);
}
