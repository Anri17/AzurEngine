#include "CollisionManager.h"

std::vector<BoxColliderComponent*> CollisionManager::colliders;

void CollisionManager::Update()
{
	// check every collision for overlap
	// If they overlap, change their state,
	// ie, if they are colliding,
	// and what are the colliders that are overlapping.

	// Reset Collider Data First
	
	for (size_t i = 0; i < colliders.size(); ++i)
	{
		colliders[i]->isColliding = false;
		for (size_t j = 0; j < colliders[i]->collision_references.size(); ++j)
			colliders[i]->collision_references.pop_back();
		for (size_t j = 0; j < colliders[i]->collision_tags.size(); ++j)
			colliders[i]->collision_tags.pop_back();
	}

	// Check for Collisions and set the respective data for each collider
	for (size_t i = 0; i < colliders.size(); ++i)
	{
		BoxColliderComponent* collider0 = colliders[i];
		// We don't need to evaluate collisions for inactie entities
		if (!collider0->entity->active) continue;


		for (size_t j = i + 1; j < colliders.size(); ++j)
		{
			BoxColliderComponent* collider1 = colliders[j];
			// We don't need to evaluate collisions for inactie entities
			if (!collider1->entity->active) continue;


			bool is_colliding = collider0->true_top < collider1->true_bottom && collider0->true_left < collider1->true_right &&
				collider1->true_top < collider0->true_bottom && collider1->true_left < collider0->true_right;
			if (is_colliding)
			{
				/*
					add collider references to the colliders
					add collider tags to the collider, if that tag doesn't already exist in that collider's tag vector.,
					set that it is colliding with something.
				*/
				//TODO

				collider0->isColliding = true;
				collider1->isColliding = true;

				collider0->collision_references.push_back(collider1);
				collider1->collision_references.push_back(collider0);

				bool add_tag_0 = true;
				bool add_tag_1 = true;
				for (size_t k = 0; k < collider0->collision_tags.size(); ++k)
				{
					if (collider0->collision_tags[k] == collider1->collisionTagName)
					{
						add_tag_0 = false;
						break;
					}
				}
				for (size_t k = 0; k < collider1->collision_tags.size(); ++k)
				{
					if (collider1->collision_tags[k] == collider0->collisionTagName)
					{
						add_tag_1 = false;
						break;
					}
				}
				if (add_tag_0) collider0->collision_tags.push_back(collider1->collisionTagName);
				if (add_tag_1) collider1->collision_tags.push_back(collider0->collisionTagName);
			}
		}
	}
}

void CollisionManager::AddCollider(BoxColliderComponent* collider)
{
	colliders.push_back(collider);
}

void CollisionManager::RemoveCollider(BoxColliderComponent* collider)
{
	std::vector<BoxColliderComponent*>::iterator pos = std::find(colliders.begin(), colliders.end(), collider);
	if (pos != colliders.end())
	{
		colliders.erase(pos);
	}
}
