#include "Collider.h"

void Collider::Init()
{
	isColliding = false;
	collider_references = {};
	collider_tags = {};
}

Collider::~Collider()
{

}