#ifndef CORE_H
#define CORE_H

#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#include "Input.h"
#include "MachineState.h"

enum sound {
	MENU_MOVE,
	SNAKE_EAT
};

class Core
{
public:
	Core();
	~Core();

	bool Init();
	void Destroy();
	SDL_Window* getWindow();
	SDL_Renderer* getRenderer();
	SDL_Event event;
	TTF_Font* getFont();
	Input* getInput();
	void playSound(sound effect);

	void updateEvent();

protected:


private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	TTF_Font* font;
	Input input;

	Mix_Chunk* menu_move;
	Mix_Chunk* snake_eat;
};

#endif // !CORE_H

