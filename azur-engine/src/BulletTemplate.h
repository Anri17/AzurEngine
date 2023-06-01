#ifndef _BULLET_TEMPLATE_H
#define _BULLET_TEMPLATE_H

#include "ECS.h"

struct BulletTemplate
{
	ECS_Tag tag;
	BulletType type;
	int circle_collider_radius;
	Sprite* sprite;
};

#endif // _BULLET_TEMPLATE_H