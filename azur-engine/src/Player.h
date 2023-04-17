#ifndef _PLAYER_H
#define _PLAYER_H

#include "ECS.h"
#include "Components.h"

class Player : public Entity
{
public:
	Player(SDL_Renderer* renderer);
	void Logic();

	PositionComponent* position;

	int player_w = 32; // TODO: Get the sprite w through the SDL_Rect.
	int player_h = 48; // TODO: Get the sprite h through the SDL_Rect.
	float spawnX = 320.0f;
	float spawnY = 400.0f;
};


#endif // _PLAYER_H