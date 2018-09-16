#pragma once
#include "Components.hpp"
#include "../TextureManager.hpp"
#include "SDL.h"

class SpriteComponent : public Component
{
public:
	SpriteComponent() = default;
	SpriteComponent(const char* path) {
		setTex(path);
	};

	void setTex(const char* path) {
		texture = TextureManager::LoadTexure(path);
	}

	void init() override {

		//initializse position as a entity a component of type Position Component
		transform = &entity->getComponent<TransformComponent>();

		srcRect.x = srcRect.y = 0;
		srcRect.w = srcRect.h = 32;
		destRect.w = destRect.h = 64;
	}
	void update() override {
		destRect.x = transform->x();
		destRect.y = transform->y();
	}
	void draw() override {
		TextureManager::Draw(texture, srcRect, destRect);
	}



private:
	//reference to the posiiton because spritecomponent is responsible for drawing itself on the screen
	TransformComponent* transform;
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;

};
