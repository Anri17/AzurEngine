#ifndef _COLLIDER_COMPONENT_H
#define _COLLIDER_COMPONENT_H

#include <vector>

#include ".\..\ECS.h"

#include "Position.h"

enum class ColliderType
{
	BASE,
	BOX,
	CIRCLE
};

class Collider : public Component
{
public:
	void Init() override;

	~Collider() override;
public:
	ColliderType type = ColliderType::BASE;
	bool isColliding;
	std::vector<Collider*> collider_references;
	std::vector<ECS::Tag> collider_tags;
};

#endif // _COLLIDER_COMPONENT_H
