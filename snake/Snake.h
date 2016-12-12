#ifndef SNAKE_H
#define SNAKE_H

#include "Core.h"
#include "Map.h"
#include "Vector2.h"
#include <vector>
#include <sstream>


class Snake
{
public:
	Snake(Core* _core, Map* _map);
	~Snake();

	void Reset();
	void Update();
	void Draw();
	void Handle();

	int score;
	bool die;
protected:
	void addPart();
	bool checkWall();
	void checkFood();
private:
	Core* core;
	Map* map;
	std::stringstream ss;

	Vector2 currentDirection;
	std::vector<Vector2> part;

	SDL_Texture* scoreTex;
	SDL_Rect scoreRect;

	SDL_Rect tmpRect;
	Vector2 preVector;
};

#endif // !SNAKE_H
