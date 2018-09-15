#pragma once
#include "Game.hpp"
class GameObject
{
public:
	GameObject(const char* texturesheet, SDL_Renderer* rend, int x , int y);
	~GameObject();

	void Update();
	void Render();

private:
	int xPosition,
		yPosition;

	SDL_Texture* objTexture;
	SDL_Rect srcRect, destRect;
	SDL_Renderer* renderer;

};

