#include "PlayState.h"



PlayState::PlayState(Core* _core) :
	core(_core)
{
}


PlayState::~PlayState()
{
}

void PlayState::Init() {
	this->map = new Map(core);
	this->snake = new Snake(core, map);
	this->panel = new Panel(core);
	this->gamePaused = false;
}

void PlayState::Update() {
	if (!this->gamePaused) {
		this->map->Update();

		this->snake->Update();

		if (this->snake->die) this->gamePaused = true;

		this->panel->visible = false;
	}

	else {
		this->panel->visible = true;
	}


}

void PlayState::Draw() {
	SDL_SetRenderDrawBlendMode(core->getRenderer(), SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(core->getRenderer(), 0, 0, 0, 255);
	SDL_RenderClear(core->getRenderer());

	if (!this->gamePaused) {

		this->map->Draw();

		this->snake->Draw();
	}

	else if (this->panel->visible) {
		this->panel->Draw(this->snake->score);
	}
	SDL_RenderPresent(core->getRenderer());
}

void PlayState::Handle() {
	if (this->snake->die) {
		if (core->getInput()->wasKeyPressed(SDL_SCANCODE_RETURN)) {
			this->snake->Reset();
			this->gamePaused = false;
		}
		else if (core->getInput()->wasKeyPressed(SDL_SCANCODE_ESCAPE)) MachineState::getInstance()->changeState(new LogoState(core));
	}
	else {
		if (core->getInput()->wasKeyPressed(SDL_SCANCODE_ESCAPE)) MachineState::getInstance()->changeState(new LogoState(core));
		else if (core->getInput()->wasKeyPressed(SDL_SCANCODE_RETURN)) this->gamePaused = !this->gamePaused;
		this->snake->Handle();
	}
}

void PlayState::Exit() {

}