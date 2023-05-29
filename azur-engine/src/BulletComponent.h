#ifndef _BULLET_H
#define _BULLET_H

#include "ECS.h"
#include "PositionComponent.h"

class ColliderComponent;

#include "AzurMemoryLeakFinder.h"

#include "vector2float.h"

class BulletComponent : public Component
{
public:
	void init() override;
	void update() override;

	PositionComponent* position;
	ColliderComponent* collider;
	int width = 12;
	int height = 12;

	float speed = 1.0f;
	float angle = 0.0f;
private:
	vector2float velocity;

	int deletion_timer_frame = 0;
	int deletion_cooldown = 60; // 1 seconds
};

#endif // _BULLET_H