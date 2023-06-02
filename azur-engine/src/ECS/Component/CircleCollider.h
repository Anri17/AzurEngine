#ifndef _CIRCLE_COLLIDER_COMPONENT_H
#define _CIRCLE_COLLIDER_COMPONENT_H

#include ".\..\ECS_Component.h"

#include "Collider.h"

namespace ECS
{
	class CircleCollider : public Collider
	{
	public:
		void init() override;

	public:
		float radius;
	};
}

#endif // _CIRCLE_COLLIDER_COMPONENT_H
