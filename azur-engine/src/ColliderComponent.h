#ifndef _COLLIDER_COMPONENT_H
#define _COLLIDER_COMPONENT_H

#include <vector>

#include "ECS.h"
#include "PositionComponent.h"
#include "ColliderTag.h"

enum class ColliderType
{
	BASE,
	BOX,
	CIRCLE
};

class ColliderComponent : public Component
{
public:
	void init() override;

	~ColliderComponent() override;
public:
	// A reference to the position component of this component's entity 
	PositionComponent* position;
	ColliderTag tag;
	ColliderType type = ColliderType::BASE;
	bool isColliding;
	std::vector<ColliderComponent*> collider_references;
	std::vector<ColliderTag> collider_tags;
};

#endif // _COLLIDER_COMPONENT_H
