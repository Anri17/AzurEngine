#ifndef _CIRCLE_COLLIDER_COMPONENT_H
#define _CIRCLE_COLLIDER_COMPONENT_H

#include "ColliderComponent.h"

class CircleColliderComponent : public ColliderComponent
{
public:
	void init() override;
	void update() override;
	void draw(SDL_Renderer* renderer) override;

public:
	float radius;
};


#endif // _CIRCLE_COLLIDER_COMPONENT_H
