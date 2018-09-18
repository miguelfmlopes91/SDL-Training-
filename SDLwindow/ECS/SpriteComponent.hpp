#pragma once
#include "Components.hpp"
#include "../TextureManager.hpp"
#include "SDL.h"

class SpriteComponent : public Component
{
private:
	//reference to the posiiton because spritecomponent is responsible for drawing itself on the screen
	TransformComponent* transform;
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;

	bool animated = false;
	int frames = 0; //number of frames in animations
	int speed = 100; //delay between frames in miliseconds

public:
	SpriteComponent() = default;
	SpriteComponent(const char* path) {
		setTex(path);
	};
	SpriteComponent(const char* path, int nFrames, int mSpeed) {
		animated = true;
		frames = nFrames;
		speed = mSpeed;
		setTex(path);
	};
	~SpriteComponent() {
		SDL_DestroyTexture(texture);
	}



	void setTex(const char* path) {
		texture = TextureManager::LoadTexure(path);
	}

	void init() override {

		//initializse position as a entity a component of type Position Component
		transform = &entity->getComponent<TransformComponent>();

		srcRect.x = srcRect.y = 0;
		srcRect.w = transform->width;
		srcRect.h = transform->height;

	}
	void update() override {

		if (animated)
		{
			srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / speed % frames));
		}

		destRect.x = static_cast<int>(transform->position.x);
		destRect.y = static_cast<int>(transform->position.y);
		destRect.w = transform->width * transform->scale;
		destRect.h = transform->height * transform->scale;
	}
	void draw() override {
		TextureManager::Draw(texture, srcRect, destRect);
	}

};
