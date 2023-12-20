#include "Collider.h"

void Collider::Init() {
	type =                ColliderType::BASE;
	isColliding =         false;
	collider_references = {};
	collider_tags =       {};
}

Collider::~Collider() { }