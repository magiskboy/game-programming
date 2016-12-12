#ifndef INPUT_H
#define INPUT_H

#include <map>
#include "SDL.h"
#include "Vector2.h"

class Input
{
public:
	Input();
	~Input();

	void beginNewFrame();
	void keyUpEvent(const SDL_Event& event);
	void keyDownEvent(const SDL_Event& event);
	void mouseMotion();

	bool wasKeyPressed(SDL_Scancode key);
	bool wasKeyReleased(SDL_Scancode key);
	bool isKeyHeld(SDL_Scancode key);

	void mouseUpEvent(const SDL_Event& event);
	void mouseDownEvent(const SDL_Event& event);

	bool wasMousePressed(int code);
	bool wasMouseReleased(int code);
	bool wasMouseHeld(int code);

	Vector2 getPosition();

private:
	std::map<SDL_Scancode, bool> _heldKeys;
	std::map<SDL_Scancode, bool> _pressedKeys;
	std::map<SDL_Scancode, bool> _releasedKeys;

	std::map<int, bool> _heldButton;
	std::map<int, bool> _pressedButton;
	std::map<int, bool> _releasedButton;

	Vector2 mousePosition;
};


#endif // !INPUT_H
