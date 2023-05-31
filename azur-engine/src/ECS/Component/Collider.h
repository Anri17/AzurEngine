#ifndef _COLLIDER_COMPONENT_H
#define _COLLIDER_COMPONENT_H

#include <vector>

#include ".\..\ECS_Component.h"

#include "Position.h"

namespace ECS
{
	enum class ColliderType
	{
		BASE,
		BOX,
		CIRCLE
	};

	class Collider : public Component
	{
	public:
		void init() override;

		~Collider() override;
	public:
		// A reference to the position component of this component's entity 
		Position* position;
		ColliderType type = ColliderType::BASE;
		bool isColliding;
		std::vector<Collider*> collider_references;
		std::vector<ECS_Tag> collider_tags;
	};
}

#endif // _COLLIDER_COMPONENT_H
