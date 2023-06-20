#ifndef _BULLET_TEMPLATE_H
#define _BULLET_TEMPLATE_H

#include "Components.h"
#include "SpriteData.h"
#include "ECS.h"

struct BulletTemplate
{
	ECS::Tag tag;
	BulletType type;
	int circle_collider_radius;
	SpriteData* sprite;
};

#endif // _BULLET_TEMPLATE_H