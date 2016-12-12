#include "Panel.h"



Panel::Panel(Core* _core):
	core(_core)
{
	SDL_Color cl = { 255, 255, 255 };
	visible = false;
	body = { 100, 115, 420, 250 };
	this->rect[0] = { 110, 125, 400, 60 };
	this->rect[1] = { 120, 200, 380, 40 };
	this->rect[2] = { 120, 250, 300, 40 };
	score = -1;

	/*ss << "Yours score: " << -1;
	this->tex[0] = SDL_CreateTextureFromSurface(core->getRenderer(), TTF_RenderText_Blended(core->getFont(), ss.str().c_str(), cl));
	ss.str("");*/
	ss << "Press enter to continue or play again";
	this->tex[1] = SDL_CreateTextureFromSurface(core->getRenderer(), TTF_RenderText_Blended(core->getFont(), ss.str().c_str(), cl));
	ss.str("");
	ss << "Press ESC on the menu";
	this->tex[2] = SDL_CreateTextureFromSurface(core->getRenderer(), TTF_RenderText_Blended(core->getFont(), ss.str().c_str(), cl));
}


Panel::~Panel()
{
}

void Panel::Handle() {

}

void Panel::Draw(int _score) {
	SDL_SetRenderDrawColor(core->getRenderer(), 148, 148, 148, 3);
	SDL_RenderFillRect(core->getRenderer(), &body);

	if (this->score != _score) {
		ss.str("");
		SDL_Color cl = { 255, 255, 255 };
		ss << "Yours score: " << _score;
		this->tex[0] = SDL_CreateTextureFromSurface(core->getRenderer(), TTF_RenderText_Blended(core->getFont(), ss.str().c_str(), cl));
		for(int i = 0; i < 3; i++)
			SDL_RenderCopy(core->getRenderer(), this->tex[i], NULL, &this->rect[i]);
	}

}
