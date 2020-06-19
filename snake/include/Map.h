#ifndef MAP_H
#define MAP_H

#include "Core.h"
#include "Vector2.h"
#include <ctime>
#include <cstdlib>

const int MAP_UNIT = 15;
const int MAP_WIDTH = 480 / MAP_UNIT;
const int MAP_HEIGHT = 480 / MAP_UNIT;

class Map
{
public:
	Map(Core* _core);
	~Map();

	void Update();
	void Draw();
	Vector2 food;
private:
	Core* core;

	SDL_Rect matrix[MAP_WIDTH][MAP_HEIGHT];
	SDL_Rect wall[4];
};

#endif // !MAP_H
