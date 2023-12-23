#ifndef _BULLET_SPAWNER_COMPONENT_H
#define _BULLET_SPAWNER_COMPONENT_H

#include "./../ECS.h"

#include "Position.h"

class BulletSpawner : public Component {
public:
	void Init() override;
	void Update() override;

	~BulletSpawner() override;
private:
	Position *position;
	int      frame;
	float    bullet_angle;
	float    full_pattern_angle_offset;
};

#endif // _BULLET_SPAWNER_COMPONENT_H