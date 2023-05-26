#ifndef _BULLET_TEMPLATE_H
#define _BULLET_TEMPLATE_H

#include "Sprite.h"
#include "BulletType.h"
#include "ECS.h"

struct BulletTemplate
{
	EntityTag tag;
	BulletType type;
	int circle_collider_radius;
	Sprite* sprite;
};

#endif // _BULLET_TEMPLATE_H