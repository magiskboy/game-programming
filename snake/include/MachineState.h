#ifndef MACHINESTATE_H
#define MACHINESTATE_H

#include "State.h"
#include <stddef.h>

class MachineState
{
public:
	static MachineState* getInstance();
	~MachineState();

	void Update();
	void Handle();
	void changeState(State* state);
	bool isRunning;

protected:
	MachineState();
	static MachineState* Instace;

private:
	State* currentState;
	State* nextState;
};

#endif // !MACHINESTATE_H

