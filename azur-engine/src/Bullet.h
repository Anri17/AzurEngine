#pragma once
#ifndef _BULLET_H
#define _BULLET_H

#include "ECS.h"
#include "Components.h"

class Bullet : public Entity
{
public:
	Bullet(SDL_Renderer* renderer, float x, float y);


	PositionComponent* position;

	void Logic();

	int width = 12;
	int height = 12;
};

#endif // _BULLET_H