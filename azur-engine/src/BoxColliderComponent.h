#ifndef _BOX_COLLIDER_COMPONENT_H
#define _BOX_COLLIDER_COMPONENT_H

#include "Debug.h"

#include "ColliderComponent.h"

class BoxColliderComponent : public ColliderComponent
{
public:
	void draw(SDL_Renderer* renderer) override;
	void update() override;
	void init() override;

public:
	float offset_top;
	float offset_right;
	float offset_bottom;
	float offset_left;

	float true_top;
	float true_right;
	float true_bottom;
	float true_left;
};




#endif // _BOX_COLLIDER_COMPONENT_H