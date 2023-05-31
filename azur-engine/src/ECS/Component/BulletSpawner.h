#ifndef _BULLET_SPAWNER_COMPONENT_H
#define _BULLET_SPAWNER_COMPONENT_H

#include ".\..\ECS_Component.h"

#include "Position.h"

namespace ECS
{

	class BulletSpawner : public Component
	{
	public:
		void init() override;
		void update() override;

		~BulletSpawner() override;
	private:
		Position* position;
		int frame;
		float bullet_angle = 0;
		float full_pattern_angle_offset = 0;
	};
}

#endif // _BULLET_SPAWNER_COMPONENT_H