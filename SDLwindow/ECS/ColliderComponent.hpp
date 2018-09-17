#pragma once
#include <string.h>
#include "SDL.h"
#include "Components.hpp"

class ColliderComponent : public Component
{
	SDL_Rect collider;
	std::string tag;

	TransformComponent* transform;

	void init() override {
		//make sure we have transform component in our entity
		if (!entity->hasComponent<TransformComponent>())
		{
			entity->addComponent<TransformComponent>();
		}
		transform = &entity->getComponent<TransformComponent>();
	}

};