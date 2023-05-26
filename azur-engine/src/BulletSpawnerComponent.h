#ifndef _BULLET_SPAWNER_COMPONENT_H
#define _BULLET_SPAWNER_COMPONENT_H

#include "ECS.h"
#include "PositionComponent.h"

class BulletSpawerComponent : public Component
{
public:
	void init() override;
	void update() override;

	~BulletSpawerComponent() override;
private:
	PositionComponent* position;
	int frame;
	int bullet_angle = 0;
	int full_pattern_angle_offset = 0;
};


#endif // _BULLET_SPAWNER_COMPONENT_H