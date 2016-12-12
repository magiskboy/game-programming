#include "Map.h"



Map::Map(Core* _core):
	core(_core)
{
	for (int j = 0; j < MAP_HEIGHT; j++)
		for (int i = 0; i < MAP_WIDTH; i++)
			this->matrix[i][j] = { i * MAP_UNIT , j * MAP_UNIT, MAP_UNIT, MAP_UNIT };

	this->wall[0] = { 0, 0, MAP_WIDTH * MAP_UNIT, MAP_UNIT };
	this->wall[1] = { 0, 0, MAP_UNIT * 1, MAP_UNIT * MAP_HEIGHT};
	this->wall[2] = { 0, (MAP_HEIGHT - 1) * MAP_UNIT, MAP_WIDTH * MAP_UNIT, MAP_UNIT * 1};
	this->wall[3] = { MAP_WIDTH * MAP_UNIT, 0, MAP_UNIT * 1, MAP_UNIT * MAP_HEIGHT};
	this->food = Vector2(-1, -1);
}


Map::~Map()
{
}

void Map::Update() {
	if (this->food == Vector2(-1, -1)) {
		srand(time(NULL));
		this->food = Vector2(rand() % (MAP_WIDTH - 2) + 1, rand() % (MAP_HEIGHT - 2) + 1);
	}
}

void Map::Draw() {
	// Draw Grid
	/*SDL_SetRenderDrawColor(core->getRenderer(), 0, 255, 0, 255);
	for (int i = 0; i < MAP_WIDTH; i++)
		SDL_RenderDrawLine(core->getRenderer(), i * MAP_UNIT, 0, i * MAP_UNIT, MAP_HEIGHT * MAP_UNIT);
	for (int i = 0; i < MAP_HEIGHT; i++)
		SDL_RenderDrawLine(core->getRenderer(), 0, i * MAP_UNIT, MAP_WIDTH * MAP_UNIT, i * MAP_UNIT);*/

	// Draw Wall
	SDL_SetRenderDrawColor(core->getRenderer(), 255, 255, 255, 255);
	for (int i = 0; i < 4; i++) SDL_RenderFillRect(core->getRenderer(), &this->wall[i]);

	SDL_SetRenderDrawColor(core->getRenderer(), 0, 0, 255, 255);
	SDL_Rect tmp = { this->food.x * MAP_UNIT, this->food.y * MAP_UNIT, MAP_UNIT, MAP_UNIT };
	SDL_RenderFillRect(core->getRenderer(), &tmp);

}
