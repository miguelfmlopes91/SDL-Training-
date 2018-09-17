#pragma once
#include "ECS.hpp"
#include "TransformComponent.hpp"
#include "SDL.h"

class TileComponent : public Component {

public:
	TransformComponent* transform;
	SpriteComponent* sprite;

	SDL_Rect tileRect;
	int tileID;
	const char * path;

	TileComponent() = default;

	TileComponent(int x, int y, int w, int h, int id) {
		tileRect.x = x;
		tileRect.y = y;
		tileRect.w = w;
		tileRect.h = h;
		tileID = id;

		switch (tileID)
		{
		case 0:
			path = "Resources/water.png";
			break;
		case 1:
			path = "Resources/dirt.png";
			break;
		case 2:
			path = "Resources/grass.png";
			break;
		default:
			break;
		}
	}

	void init()override {
		//add transform compoonent to the tile
		entity->addComponent<TransformComponent>(tileRect.x, tileRect.y, tileRect.w, tileRect.h, 1);
		transform = &entity->getComponent<TransformComponent>();

		entity->addComponent<SpriteComponent>(path);
		sprite = &entity->getComponent<SpriteComponent>();

	}

};