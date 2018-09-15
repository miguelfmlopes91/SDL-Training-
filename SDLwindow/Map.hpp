#pragma once
#include <string>
#include "Game.hpp"

class Map
{
public:
	Map();
	//Map(std::string tID, int ms, int ts);
	~Map();

	//void LoadMap(std::string path, int sizeX, int sizeY);
	void LoadMap(int arr[20][25]);
	void DrawMap();
	//void AddTile(int srcX, int srcY, int xpos, int ypos);

private:
	//std::string texID;
	//int mapScale;
	//int tileSize;
	//int scaledSize;
	SDL_Rect src, dest;

	SDL_Texture* dirt;
	SDL_Texture* grass;
	SDL_Texture* water;

	int map[20][25];
};
