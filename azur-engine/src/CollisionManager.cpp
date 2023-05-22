#include "CollisionManager.h"

std::vector<ColliderComponent*> CollisionManager::colliders;

void CollisionManager::Update()
{
	// Check every collision for overlap
	// If they overlap, change their state.
	
	// Reset Collider Data First
	for (size_t i = 0; i < colliders.size(); ++i)
	{
		colliders[i]->isColliding = false;
		for (size_t j = 0; j < colliders[i]->collider_references.size(); ++j)
			colliders[i]->collider_references.pop_back();
		for (size_t j = 0; j < colliders[i]->collider_tags.size(); ++j)
			colliders[i]->collider_tags.pop_back();
	}

	// TODO: THIS IS FOR BOXCOLLIDER ONLY. A test check needs to be made for circle colliders.
	// TODO: This is only set up for the mean time so that the program compiles. 
	// Check for Collisions and set the respective data for each collider
	for (size_t i = 0; i < colliders.size(); ++i)
	{
		// TODO: Test BoxColliders agains Circle Colliders.
		// TODO: At this moment this is only working with BoxColliders
		// WARNING: TODO: The moment a CircleColliderComponent is added to vector of colliders, everything breaks.
		BoxColliderComponent* collider0 = (BoxColliderComponent*)colliders[i];
		// We don't need to evaluate collisions for inactie entities
		if (!collider0->entity->active) continue;


		for (size_t j = i + 1; j < colliders.size(); ++j)
		{
			// TODO: Test BoxColliders agains Circle Colliders.
			// TODO: At this moment this is only working with BoxColliders
			BoxColliderComponent* collider1 = (BoxColliderComponent*)colliders[j];
			// We don't need to evaluate collisions for inactie entities
			if (!collider1->entity->active) continue;


			// TODO: I can probably replace all of this with a simple distance check between the two neared points of each collision border.
			// TODO: This implementation would work for both ovals and squares.
			// TODO: Another solutions would be if two lines intersect, thought that would probably require my to convert the data into usable linear functions with which I could make that kind of calculation.
			// TODO: Think of a star shaped Collider. The closed points would probalby be the vertices of the star. The implementation would be different because the shape is concave.
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

				collider0->collider_references.push_back(collider1);
				collider1->collider_references.push_back(collider0);

				bool add_tag_0 = true;
				bool add_tag_1 = true;
				for (size_t k = 0; k < collider0->collider_tags.size(); ++k)
				{
					if (collider0->collider_tags[k] == collider1->tag)
					{
						add_tag_0 = false;
						break;
					}
				}
				for (size_t k = 0; k < collider1->collider_tags.size(); ++k)
				{
					if (collider1->collider_tags[k] == collider0->tag)
					{
						add_tag_1 = false;
						break;
					}
				}
				if (add_tag_0) collider0->collider_tags.push_back(collider1->tag);
				if (add_tag_1) collider1->collider_tags.push_back(collider0->tag);
			}
		}
	}
}

void CollisionManager::AddCollider(ColliderComponent* collider)
{
	colliders.push_back(collider);
}

void CollisionManager::RemoveCollider(ColliderComponent* collider)
{
	std::vector<ColliderComponent*>::iterator pos = std::find(colliders.begin(), colliders.end(), collider);
	if (pos != colliders.end())
	{
		colliders.erase(pos);
	}
}
