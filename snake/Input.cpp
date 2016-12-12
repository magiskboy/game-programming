#include "Input.h"



Input::Input(){

}


Input::~Input(){

}

void Input::beginNewFrame() {
	this->_pressedKeys.clear();
	this->_releasedKeys.clear();
	this->_pressedButton.clear(); 
	this->_releasedButton.clear();
}

void Input::keyUpEvent(const SDL_Event& event) {
	this->_heldKeys[event.key.keysym.scancode] = false;
	this->_releasedKeys[event.key.keysym.scancode] = true;
}

void Input::keyDownEvent(const SDL_Event& event) {
	this->_pressedKeys[event.key.keysym.scancode] = true;
	this->_heldKeys[event.key.keysym.scancode] = true;
}

bool Input::isKeyHeld(SDL_Scancode key) {
	return this->_heldKeys[key];
}

bool Input::wasKeyPressed(SDL_Scancode key) {
	return this->_pressedKeys[key];
}

bool Input::wasKeyReleased(SDL_Scancode key) {
	return this->_releasedKeys[key];
}

void Input::mouseMotion() {
	SDL_GetMouseState(&mousePosition.x, &mousePosition.y);
	
}

Vector2 Input::getPosition() {
	return this->mousePosition;
}

bool Input::wasMouseHeld(int code) {
	return this->_heldButton[SDL_BUTTON(code)];
}

bool Input::wasMousePressed(int code) {
	return this->_pressedButton[SDL_BUTTON(code)];
}

bool Input::wasMouseReleased(int code) {
	return this->_releasedButton[SDL_BUTTON(code)];
}

void Input::mouseUpEvent(const SDL_Event& event) {
	int typeButton;
	if (event.button.button == SDL_BUTTON_LEFT) typeButton = 1;
	else if (event.button.button == SDL_BUTTON_RIGHT) typeButton = 4;
	else typeButton = 2;
	this->_releasedButton[typeButton] = true;
	this->_heldButton[typeButton] = false;

}

void Input::mouseDownEvent(const SDL_Event& event) {
	int typeButton;
	if (event.button.button == SDL_BUTTON_LEFT) typeButton = 1;
	else if (event.button.button == SDL_BUTTON_RIGHT) typeButton = 4;
	else typeButton = 2;
	this->_pressedButton[typeButton] = true;
	this->_heldButton[typeButton] = true;

}