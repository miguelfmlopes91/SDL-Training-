#include "GameObject.hpp"
#include "TextureManager.hpp"


GameObject::GameObject(const char * texturesheet, SDL_Renderer * rend, int x, int y)
{
	renderer = rend;
	objTexture = TextureManager::LoadTexure(texturesheet, rend);

	xPosition = x;
	yPosition = y;
}

GameObject::~GameObject()
{
}

void GameObject::Update()
{
	xPosition++;
	yPosition++;

	srcRect.h = 50;
	srcRect.w = 50;
	srcRect.x = 0;
	srcRect.y = 0;

	destRect.x = xPosition;
	destRect.y = yPosition;
	destRect.w = srcRect.w * 2;
	destRect.h = srcRect.h * 2;
}

void GameObject::Render()
{
	SDL_RenderCopy(renderer,objTexture, &srcRect, &destRect);
}
