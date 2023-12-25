#include "Mouse.h"

Mouse::Mouse() : xPos(0), yPos(0), MouseState(0) {}

Mouse::~Mouse() { }

void Mouse::Update() {
	MouseState = SDL_GetMouseState(&xPos, &yPos);
}
