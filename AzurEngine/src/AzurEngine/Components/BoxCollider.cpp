#include "BoxCollider.h"

void BoxCollider::Init() {
	Collider::Init();
	type          = ColliderType::BOX;
	offset_top    = 0;
	offset_right  = 0;
	offset_bottom = 0;
	offset_left   = 0;
}
