#ifndef PANEL_H
#define PANEL_H

#include "Core.h"
#include "MachineState.h"
#include <sstream>

class Panel
{
public:
	Panel(Core* _core);
	~Panel();

	void Handle();
	void Draw(int _score);

	bool visible;
private:
	Core* core;

	SDL_Rect body;
	std::stringstream ss;
	int score;
	SDL_Texture* tex[3];
	SDL_Rect rect[3];
};


#endif // !PANEL_H
