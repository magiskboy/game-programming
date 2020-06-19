#ifndef LOGOSTATE_H
#define LOGOSTATE_H

#include "State.h"
#include "Core.h"
#include "MachineState.h"
#include "CreditState.h"
#include "PlayState.h"

enum GameState {
	PLAY,
	CREDIT,
	EXIT
};

class LogoState : public State
{
public:
	LogoState(Core* _core);
	~LogoState();

	void Init();
	void Update();
	void Draw();
	void Handle();
	void Exit();

private:
	Core* core;
	GameState choiceState;

	SDL_Texture* logoTexture;
	SDL_Texture* playTexture;
	SDL_Texture* creditTexture;
	SDL_Texture* exitTexture;

	SDL_Rect logoRect;
	SDL_Rect playRect;
	SDL_Rect creditRect;
	SDL_Rect exitRect;

};


#endif // !LOGOSTATE_H

