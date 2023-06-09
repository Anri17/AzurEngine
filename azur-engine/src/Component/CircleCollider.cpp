#include "CircleCollider.h"

void CircleCollider::Init()
{
	Collider::Init();
	type = ColliderType::CIRCLE;
	radius = 1.0f;
}
