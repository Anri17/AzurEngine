#ifndef _BULLET_H
#define _BULLET_H

#include "ECS.h"
#include "PositionComponent.h"

#include "AzurMemoryLeakFinder.h"

#include "vector2float.h"

class BulletComponent : public Component
{
public:
	void init() override;
	void update() override;

	PositionComponent* position;
	int width = 12;
	int height = 12;

	float speed = 1.0f;
	float angle = 0.0f;
private:
	vector2float velocity;
};

#endif // _BULLET_H