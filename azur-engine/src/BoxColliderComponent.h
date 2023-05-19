#ifndef _BOX_COLLIDER_COMPONENT_H
#define _BOX_COLLIDER_COMPONENT_H

#include "Debug.h"
#include "ECS.h"
#include "PositionComponent.h"

#include "EntityTag.h"

class BoxColliderComponent : public Component
{
public:
	void draw(SDL_Renderer* renderer) override;
	void update() override;
	void init() override;
	~BoxColliderComponent() override;

public:
	float offset_top;
	float offset_right;
	float offset_bottom;
	float offset_left;

	float true_top;
	float true_right;
	float true_bottom;
	float true_left;

	// A reference to the position component of this component's entity 
	PositionComponent* position;

	EntityCollisionTag collisionTagName;

	bool isColliding;
	std::vector<BoxColliderComponent*> collision_references;
	std::vector<EntityCollisionTag> collision_tags;
};




#endif // _BOX_COLLIDER_COMPONENT_H