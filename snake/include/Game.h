#ifndef GAME_H
#define GAME_H

#include "Core.h"
#include "MachineState.h"
#include "FPSController.h"
#include "LogoState.h"

class Game
{
public:
	Game();
	~Game();

	bool Init();
	bool Run();
	void Exit();

private:
	bool isRunning;
	
	Core core;
};


#endif // !GAME_H

