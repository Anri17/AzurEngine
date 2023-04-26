#pragma once
#ifndef _BULLET_H
#define _BULLET_H

#include "ECS.h"
#include "Components.h"

class BulletComponent : public Component
{
public:
	void init() override;
	void update() override;


	PositionComponent* position;
	int width = 12;
	int height = 12;
};

#endif // _BULLET_H