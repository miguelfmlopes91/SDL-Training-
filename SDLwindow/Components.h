#pragma once
#include "ECS.hpp"

class PositionComponent : public Component
{
private:
	int xpos;
	int ypos;

public:
	//expose and set the y and x position
	int x() { return xpos; }
	int y() { return ypos; }

	void init() override
	{
		int xpos = 0;
		int ypos = 0;
	}

	void update() override
	{
		 xpos++;
		 ypos++;
	}


	void setPos(int x, int y) {
		xpos = x;
		ypos = y;
	}
};