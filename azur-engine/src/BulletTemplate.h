#ifndef _BULLET_TEMPLATE_H
#define _BULLET_TEMPLATE_H

#include "ColliderTag.h"
#include "Sprite.h"

struct BulletTemplate
{
	ColliderTag tag;
	int circle_collider_radius;
	Sprite* sprite;
};

#endif // _BULLET_TEMPLATE_H