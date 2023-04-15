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

	float screen_boundaries_top = 40;
	float screen_boundaries_right = 440;
	float screen_boundaries_bottom = 460;
	float screen_boundaries_left = 200;
};


#endif // _PLAYER_H