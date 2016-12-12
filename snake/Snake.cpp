#include "Snake.h"



Snake::Snake(Core* _core, Map* _map):
	core(_core),
	map(_map)
{
	this->score = 0;
	this->part.push_back(Vector2(16, 16));
	this->currentDirection = Vector2(1, 0);
	this->die = false;
	SDL_Color cl = { 255, 255, 255 };
	ss << "Score: " << this->score;
	this->scoreRect = { 500, 50, 120, 40 };
	this->scoreTex = SDL_CreateTextureFromSurface(core->getRenderer(), TTF_RenderText_Blended(core->getFont(), ss.str().c_str(), cl));
}


Snake::~Snake()
{
}

void Snake::Update() {
	SDL_Delay(60);
	preVector = this->part.at(0);
	this->part.at(0) += this->currentDirection;
	for (int i = 1; i < this->part.size(); i++) {
		Vector2 tmp = this->part.at(i);
		this->part.at(i) = preVector;
		preVector = tmp;
	}
	this->checkFood();
	this->die = this->checkWall();
}

void Snake::Draw() {
	SDL_SetRenderDrawColor(core->getRenderer(), 255, 0, 0, 255);
	for (int i = 0; i < this->part.size(); i++) {
		int x, y;
		x = this->part.at(i).x * MAP_UNIT;
		y = this->part.at(i).y * MAP_UNIT;
		tmpRect = { x, y, MAP_UNIT, MAP_UNIT };
		SDL_RenderFillRect(core->getRenderer(), &this->tmpRect);
	}
	SDL_RenderCopy(core->getRenderer(), this->scoreTex, NULL, &this->scoreRect);
}

void Snake::Handle() {
	if (core->getInput()->isKeyHeld(SDL_SCANCODE_W)) {
		if(this->currentDirection != Vector2(0, 1))
			currentDirection = Vector2(0, -1);
	}
	else if (core->getInput()->isKeyHeld(SDL_SCANCODE_S)) {
		if(this->currentDirection != Vector2(0, 1))
			currentDirection = Vector2(0, 1);
	}
	else if (core->getInput()->isKeyHeld(SDL_SCANCODE_A)) {
		if(this->currentDirection != Vector2(1, 0))
			currentDirection = Vector2(-1, 0);
	}
	else if (core->getInput()->isKeyHeld(SDL_SCANCODE_D)) {
		if(this->currentDirection != Vector2(-1, 0))
			currentDirection = Vector2(1, 0);
	}
}

void Snake::addPart() {
	this->part.push_back(preVector);
}

bool Snake::checkWall() {
	Vector2 tmp = this->part[0];
	if (tmp.x == 0 || tmp.x == MAP_WIDTH - 1 || tmp.y == 0 || tmp.y == MAP_HEIGHT - 1) return true;
	for (int i = 1; i < this->part.size(); i++)
		if (tmp == this->part[i]) return true;
	return false;
}

void Snake::checkFood() {
	if (this->part[0] == this->map->food) {
		this->addPart();
		this->score++;
		this->map->food = Vector2(-1, -1);
		this->core->playSound(SNAKE_EAT);
		ss.str("");
		SDL_Color cl = { 255, 255, 255 };
		ss << "Score: " << this->score;
		this->scoreTex = SDL_CreateTextureFromSurface(core->getRenderer(), TTF_RenderText_Blended(core->getFont(), ss.str().c_str(), cl));
	}
}

void Snake::Reset() {
	this->score = 0;
	this->part.clear();
	this->part.push_back(Vector2(16, 16));
	this->currentDirection = Vector2(1, 0);
	this->die = false;
	SDL_Color cl = { 255, 255, 255 };
	ss.str("");
	ss << "Score: " << this->score;
	this->scoreTex = SDL_CreateTextureFromSurface(core->getRenderer(), TTF_RenderText_Blended(core->getFont(), ss.str().c_str(), cl));
}