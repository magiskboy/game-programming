#include "LogoState.h"



LogoState::LogoState(Core* _core):
	core(_core)
{}


LogoState::~LogoState()
{}

void LogoState::Init() {
	SDL_Color cl = { 255, 255, 255 };
	this->logoTexture = SDL_CreateTextureFromSurface(core->getRenderer(), TTF_RenderText_Blended(core->getFont(), "Snake", cl));
	this->playTexture = SDL_CreateTextureFromSurface(core->getRenderer(), TTF_RenderText_Blended(core->getFont(), "Play", cl));
	this->creditTexture = SDL_CreateTextureFromSurface(core->getRenderer(), TTF_RenderText_Blended(core->getFont(), "Credit", cl));
	this->exitTexture = SDL_CreateTextureFromSurface(core->getRenderer(), TTF_RenderText_Blended(core->getFont(), "Exit", cl));

	logoRect = { 70, 10, 500, 230 };
	playRect = { 200, 270, 240, 70 };
	creditRect = { 200, 330, 240, 70 };
	exitRect = { 200, 390, 240, 70 };

	choiceState = PLAY;
}

void LogoState::Update() {
	SDL_SetTextureColorMod(this->playTexture, 255, 255, 255);
	SDL_SetTextureColorMod(this->creditTexture, 255, 255, 255);
	SDL_SetTextureColorMod(this->exitTexture, 255, 255, 255);

	switch (this->choiceState)
	{
	case PLAY: SDL_SetTextureColorMod(this->playTexture, 255, 0, 0);
		break;
	case CREDIT: SDL_SetTextureColorMod(this->creditTexture, 255, 0, 0);
		break;
	case EXIT: SDL_SetTextureColorMod(this->exitTexture, 255, 0, 0);
		break;
	}
}

void LogoState::Draw() {
	SDL_SetRenderDrawColor(core->getRenderer(), 0, 0, 0, 255);
	SDL_RenderClear(core->getRenderer());

	SDL_RenderCopy(core->getRenderer(), this->logoTexture, NULL, &this->logoRect);
	SDL_RenderCopy(core->getRenderer(), this->playTexture, NULL, &this->playRect);
	SDL_RenderCopy(core->getRenderer(), this->creditTexture, NULL, &this->creditRect);
	SDL_RenderCopy(core->getRenderer(), this->exitTexture, NULL, &this->exitRect);


	SDL_RenderPresent(core->getRenderer());
}

void LogoState::Handle() {
	if (core->getInput()->wasKeyPressed(SDL_SCANCODE_DOWN)) {
		switch (choiceState)
		{
		case PLAY: choiceState = CREDIT;
			break;
		case CREDIT: choiceState = EXIT;
			break;
		case EXIT: choiceState = PLAY;
			break;
		}
		core->playSound(MENU_MOVE);
	}
	else if (core->getInput()->wasKeyPressed(SDL_SCANCODE_UP)) {
		switch (choiceState)
		{
		case PLAY: choiceState = EXIT;
			break;
		case CREDIT: choiceState = PLAY;
			break;
		case EXIT: choiceState = CREDIT;
			break;
		}
		core->playSound(MENU_MOVE);
	}
	else if (core->getInput()->wasKeyPressed(SDL_SCANCODE_RETURN)) {
		switch (this->choiceState)
		{
		case PLAY: MachineState::getInstance()->changeState(new PlayState(core));
			break;
		case CREDIT: MachineState::getInstance()->changeState(new CreditState(core));
			break;
		case EXIT: MachineState::getInstance()->isRunning = false;
			break;
		}
	}
}

void LogoState::Exit() {
	/*delete this->logoTexture;
	delete this->playTexture;
	delete this->creditTexture;
	delete this->exitTexture;*/
}
