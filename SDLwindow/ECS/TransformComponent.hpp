#pragma once

#include "Components.hpp"
#include "../Vector2D.hpp"

class TransformComponent : public Component
{

public:

	Vector2D position;
	Vector2D velocity;

	int height = 32;
	int width = 32;
	int scale = 1;

	int speed = 3;


	TransformComponent() {
		position.x = 0.0f;
		position.y = 0.0f;
	}
	TransformComponent(int sc) {
		position.x = 0.0f;
		position.y = 0.0f;
		scale = sc;
	}

	TransformComponent(int x, int y) {
		position.x = x;
		position.y = y;
	}

	TransformComponent(float x, float y, int h, int w, int sc) {
		position.x = 0.0f;
		position.y = 0.0f;
		height = h;
		width = w;
		scale = sc;
	}

	void init() override {
		velocity.x = 0;
		velocity.y = 0;
	}
	void update() override {
		position.x += static_cast<int>(velocity.x * speed);
		position.y += static_cast<int>(velocity.y * speed);
	}
};
