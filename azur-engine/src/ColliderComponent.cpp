#include "ColliderComponent.h"

#include "CollisionManager.h"

void ColliderComponent::init()
{
	position = entity->GetComponent<PositionComponent>();

	tag = ColliderTag::UNDEFINED;
	isColliding = false;
	collider_references = {};
	collider_tags = {};
	CollisionManager::AddCollider(this);
}

ColliderComponent::~ColliderComponent()
{
	CollisionManager::RemoveCollider(this);
}