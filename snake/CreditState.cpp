#include "CreditState.h"



CreditState::CreditState(Core* _core):
	core(_core)
{

}


CreditState::~CreditState()
{}

void CreditState::Init() {
	SDL_Color cl = { 255, 255, 255 };
	this->tex[0] = SDL_CreateTextureFromSurface(core->getRenderer(), TTF_RenderText_Blended(core->getFont(), "Snake Game", cl));
	this->tex[1] = SDL_CreateTextureFromSurface(core->getRenderer(), TTF_RenderText_Blended(core->getFont(), "SDL && C++", cl));
	this->tex[2] = SDL_CreateTextureFromSurface(core->getRenderer(), TTF_RenderText_Blended(core->getFont(), "Funny", cl));

	this->rect[0] = { 100, 30, 400, 70 };
	this->rect[1] = { 100, 140, 200, 30 };
	this->rect[2] = { 100, 190, 150, 30 };
}

void CreditState::Update() {

}

void CreditState::Draw() {
	SDL_SetRenderDrawColor(core->getRenderer(), 0, 0, 0, 255);
	SDL_RenderClear(core->getRenderer());

	SDL_RenderCopy(core->getRenderer(), this->tex[0], NULL, &this->rect[0]);
	SDL_RenderCopy(core->getRenderer(), this->tex[1], NULL, &this->rect[1]);
	SDL_RenderCopy(core->getRenderer(), this->tex[2], NULL, &this->rect[2]);

	SDL_RenderPresent(core->getRenderer());
}

void CreditState::Handle() {
	if (core->getInput()->wasKeyPressed(SDL_SCANCODE_ESCAPE)) MachineState::getInstance()->changeState(new LogoState(core));
}

void CreditState::Exit() {

}
