#include "MachineState.h"

MachineState* MachineState::Instace = 0;

MachineState::MachineState() :
	currentState(0),
	nextState(0)
{
	isRunning = true;
}


MachineState::~MachineState()
{}

MachineState* MachineState::getInstance() {
	if (Instace == NULL) Instace = new MachineState();
	return Instace;
}

void MachineState::Update() {
	if (currentState != nextState) {
		if (currentState == NULL) 
			nextState->Init();
		else {
			currentState->Exit();
			nextState->Init();
		}
		currentState = nextState;
	}

	currentState->Update();
	currentState->Draw();
}

void MachineState::Handle() {
	currentState->Handle();
}

void MachineState::changeState(State* state) {
	nextState = state;
}
