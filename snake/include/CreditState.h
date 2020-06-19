#ifndef CREDITSTATE_H
#define CREDITSTATE_H

#include "State.h"
#include "Core.h"
#include "MachineState.h"
#include "LogoState.h"

class CreditState :
	public State
{
public:
	CreditState(Core* _core);
	~CreditState();

	void Init();
	void Update();
	void Draw();
	void Handle();
	void Exit();

private:
	Core* core;

	SDL_Texture* tex[3];

	SDL_Rect rect[3];
};


#endif // !CREDITSTATE_H
