#include "ColliderComponent.h"

#include "CollisionManager.h"

void ColliderComponent::init()
{
	if (!entity->HasComponent<PositionComponent>())
		position = entity->AddComponent<PositionComponent>();
	else
		position = entity->GetComponent<PositionComponent>();

	isColliding = false;
	collider_references = {};
	collider_tags = {};
	CollisionManager::AddCollider(this);
}

ColliderComponent::~ColliderComponent()
{
	CollisionManager::RemoveCollider(this);
}