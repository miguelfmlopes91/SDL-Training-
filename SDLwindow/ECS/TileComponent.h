#pragma once

#include "ECS.hpp"
#include "../Vector2D.hpp"
#include "../Game.hpp"
#include "../TextureManager.hpp"

class TileComponent : public Component
{
public:

	SDL_Texture * texture;
	SDL_Rect srcRect, destRect;
	Vector2D position;

	TileComponent() = default;

	~TileComponent()
	{
		SDL_DestroyTexture(texture);
	}

	TileComponent(int srcX, int srcY, int xpos, int ypos, const char* path) {
		texture = TextureManager::LoadTexure(path);

		srcRect.x = srcX;
		srcRect.y = srcY;
		srcRect.w = srcRect.h = 32;
		destRect.x = xpos;
		destRect.y = ypos;
		destRect.w = destRect.h = 64;

	}

	//TileComponent(int srcX, int srcY, int xpos, int ypos, int tsize, int tscale, std::string id)
	//{
	//	//texture = Game::assets->GetTexture(id);

	//	srcRect.x = srcX;
	//	srcRect.y = srcY;
	//	srcRect.w = srcRect.h = tsize;
	//	position.x = static_cast<float>(xpos);
	//	position.y = static_cast<float>(ypos);
	//	destRect.w = destRect.h = tsize * tscale;
	//}

	void update() override
	{
		//destRect.x = static_cast<int>(position.x - Game::camera.x);
		//destRect.y = static_cast<int>(position.y - Game::camera.y);
	}
	void draw() override
	{
		TextureManager::Draw(texture, srcRect, destRect, SDL_FLIP_NONE);
	}
};