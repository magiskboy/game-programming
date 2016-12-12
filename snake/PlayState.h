#ifndef PLAYSTATE_H
#define PLAYSTATE_H

#include "State.h"
#include "Core.h"
#include "MachineState.h"
#include "LogoState.h"
#include "Map.h"
#include "Snake.h"
#include "Panel.h"

class PlayState : public State
{
public:
	PlayState(Core* _core);
	~PlayState();

	void Init();
	void Update();
	void Draw();
	void Handle();
	void Exit();
private:
	Core* core;

	Map* map;
	Snake* snake;

	bool gamePaused;

	Panel* panel;
};
#endif // !PLAYSTATE_H


