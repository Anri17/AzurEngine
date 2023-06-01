#include "Collider.h"

#include ".\..\..\CollisionManager.h"

namespace ECS
{
	void Collider::init()
	{
		if (!entity->HasComponent<Position>())
			position = entity->AddComponent<Position>();
		else
			position = entity->GetComponent<Position>();

		isColliding = false;
		collider_references = {};
		collider_tags = {};
		CollisionManager::AddCollider(this);
	}

	Collider::~Collider()
	{
		CollisionManager::RemoveCollider(this);
	}
}