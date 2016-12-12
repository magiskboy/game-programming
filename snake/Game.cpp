#include "Game.h"

#include <iostream>

Game::Game()
{}


Game::~Game()
{}

bool Game::Init() {

	if (core.Init() == false) return false;

	return true;
}

bool Game::Run() {
	if (this->Init() == false) return false;

	MachineState::getInstance()->changeState(new LogoState(&this->core));

	while (MachineState::getInstance()->isRunning){
		core.updateEvent();

		FPSController::getInstance()->beginCounter();
		MachineState::getInstance()->Update();
		FPSController::getInstance()->endCounter();
		MachineState::getInstance()->Handle();

	}

	this->Exit();

	return true;
}

void Game::Exit() {
	core.Destroy();
}