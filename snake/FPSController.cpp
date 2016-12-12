#include "FPSController.h"

FPSController* FPSController::Instance = 0;

FPSController::FPSController(){
	beginTime = SDL_GetTicks();
	delayTime = 0;
}


FPSController::~FPSController()
{
}

FPSController* FPSController::getInstance() {
	if (Instance == NULL) Instance = new FPSController();
	return Instance;
}

void FPSController::beginCounter() {
	beginTime = SDL_GetTicks();
}

void FPSController::endCounter() {
	endTime = SDL_GetTicks();
	delayTime = endTime - beginTime;
	int elapsedTime = 1000 / FPS - delayTime;
	if (elapsedTime <= 0) elapsedTime = 1;
	
	SDL_Delay(elapsedTime);
	
}