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

	float spawnX = 320.0f;
	float spawnY = 400.0f;
};


#endif // _PLAYER_H