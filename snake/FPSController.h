#ifndef FPSCONTROLLER_H
#define FPSCONTROLLER_H

#include "SDL.h"

const int FPS = 60;

class FPSController
{
public:
	static FPSController* getInstance();
	~FPSController();

	void beginCounter();
	void endCounter();
protected:
	static FPSController* Instance;
	FPSController();
private:
	unsigned long long beginTime, endTime;
	unsigned int delayTime;

};



#endif // !FPSCONTROLLER_H
