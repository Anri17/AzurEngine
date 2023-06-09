#ifndef _CIRCLE_COLLIDER_COMPONENT_H
#define _CIRCLE_COLLIDER_COMPONENT_H

#include "Collider.h"

class CircleCollider : public Collider
{
public:
	void Init() override;

public:
	float radius;
};

#endif // _CIRCLE_COLLIDER_COMPONENT_H
