#include "Core.h"

Core::Core()
{}


Core::~Core()
{}

bool Core::Init() {
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) return false;
	SDL_CreateWindowAndRenderer(640, 480, 0, &this->window, &this->renderer);
	if (this->window == NULL || this->renderer == NULL) return false;
	SDL_SetWindowTitle(this->window, "Snake");
	if (TTF_Init() < 0) return false;
	this->font = TTF_OpenFont("arial.ttf", 100);
	if (this->font == NULL) return false;
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) return false;
	this->menu_move = Mix_LoadWAV("menu_move.wav");
	this->snake_eat = Mix_LoadWAV("snake_eat.wav");
	if (this->menu_move == NULL || this->snake_eat == NULL) return false;
	return true;
}

void Core::Destroy() {
	SDL_DestroyRenderer(this->renderer);
	SDL_DestroyWindow(this->window);
	TTF_CloseFont(this->font);
	Mix_FreeChunk(this->menu_move);
	Mix_FreeChunk(this->snake_eat);
	Mix_Quit();
	TTF_Quit();
	SDL_Quit();
}

SDL_Window* Core::getWindow() {
	return this->window;
}

SDL_Renderer* Core::getRenderer() {
	return this->renderer;
}

TTF_Font* Core::getFont() {
	return this->font;
}

void Core::updateEvent() {
	input.beginNewFrame();

	if (SDL_PollEvent(&this->event) != 0) {
		if (this->event.type == SDL_QUIT) {
			//this->Destroy();
			MachineState::getInstance()->isRunning = false;
		}
		else if (this->event.type == SDL_KEYUP) this->input.keyUpEvent(this->event);
		else if (this->event.type == SDL_KEYDOWN) {
			if (this->event.key.repeat == 0) this->input.keyDownEvent(this->event);
		}
		else if (this->event.type == SDL_MOUSEMOTION) this->input.mouseMotion();
		else if (this->event.type == SDL_MOUSEBUTTONUP) this->input.mouseUpEvent(this->event);
		else if (this->event.type == SDL_MOUSEBUTTONDOWN) this->input.mouseDownEvent(this->event);
	}
}

Input* Core::getInput() {
	return &this->input;
}

void Core::playSound(sound effect) {
	switch (effect)
	{
	case MENU_MOVE: Mix_PlayChannel(-1, this->menu_move, 0);
		break;
	case SNAKE_EAT: Mix_PlayChannel(-1, this->snake_eat, 0);
		break;
	}
}