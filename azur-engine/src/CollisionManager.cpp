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
	/*

	for (size_t i = 0; i < colliders.size(); ++i)
	{
		ColliderComponent* collider0 = colliders[i];
		CircleColliderComponent* collider0_circle = nullptr;
		BoxColliderComponent* collider0_box = nullptr;
		if (colliders[i]->type == ColliderType::CIRCLE)
		{
			collider0_circle = (CircleColliderComponent*)colliders[i];
		}
		else if (colliders[i]->type == ColliderType::BOX)
		{
			collider0_box = (BoxColliderComponent*)colliders[i];
		}

		for (size_t j = i + 1; j < colliders.size(); ++j)
		{
			ColliderComponent* collider1 = colliders[j];
			CircleColliderComponent* collider1_circle = nullptr;
			BoxColliderComponent* collider1_box = nullptr;
			if (colliders[j]->type == ColliderType::CIRCLE)
			{
				collider1_circle = (CircleColliderComponent*)colliders[j];
			}
			else if (colliders[j]->type == ColliderType::BOX)
			{
				collider1_box = (BoxColliderComponent*)colliders[j];
			}


			


		}
	}
	*/


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

// returns an array of two points with the two closest points of first and second collider, respectively
std::pair<vector2float, vector2float> CollisionManager::find_closest_collision_border_point(ColliderComponent* collider0, ColliderComponent* collider1)
{
	vector2float collider0_border_point = {};
	vector2float collider1_border_point = {};
	// Get a linear function going from one collider to the other
	vector2float collider0_point = { collider0->position->x, collider0->position->y };
	vector2float collider1_point = { collider1->position->x, collider1->position->y };

	// Collider0
	if (collider0->type == ColliderType::BOX)
	{
		BoxColliderComponent* box_collider0 = (BoxColliderComponent*)collider0;
		vector2float box_collider0_p0 = { box_collider0->true_left, box_collider0->true_top };
		vector2float box_collider0_p1 = { box_collider0->true_right, box_collider0->true_top };
		vector2float box_collider0_p2 = { box_collider0->true_left, box_collider0->true_bottom };
		vector2float box_collider0_p3 = { box_collider0->true_right, box_collider0->true_bottom };

		vector2float box_collider0_border_point;

		// Check top side
		vector2float box_collider0_border_point_top = AzurMath::find_point_x(collider0_point, collider1_point, box_collider0->true_top);
		if (box_collider0_border_point_top.x > box_collider0->true_left || box_collider0_border_point_top.x < box_collider0->true_right)
		{
			collider0_border_point = box_collider0_border_point_top;
		}
		// Check right side
		vector2float box_collider0_border_point_right = AzurMath::find_point_y(collider0_point, collider1_point, box_collider0->true_right);
		if (box_collider0_border_point_right.y < box_collider0->true_top || box_collider0_border_point_right.y < box_collider0->true_bottom)
		{
			collider0_border_point = box_collider0_border_point_right;
		}
		// Check bottom side
		vector2float box_collider0_border_point_bottom = AzurMath::find_point_x(collider0_point, collider1_point, box_collider0->true_bottom);
		if (box_collider0_border_point_bottom.x > box_collider0->true_left || box_collider0_border_point_bottom.x < box_collider0->true_right)
		{
			collider0_border_point = box_collider0_border_point_bottom;
		}
		// Check bottom left
		vector2float box_collider0_border_point_left = AzurMath::find_point_y(collider0_point, collider1_point, box_collider0->true_left);
		if (box_collider0_border_point_left.y < box_collider0->true_top || box_collider0_border_point_left.y > box_collider0->true_right)
		{
			collider0_border_point = box_collider0_border_point_left;
		}
	}
	// Collider1
	if (collider1->type == ColliderType::BOX)
	{
		BoxColliderComponent* box_collider1 = (BoxColliderComponent*)collider1;
		vector2float box_collider1_p0 = { box_collider1->true_left, box_collider1->true_top };
		vector2float box_collider1_p1 = { box_collider1->true_right, box_collider1->true_top };
		vector2float box_collider1_p2 = { box_collider1->true_left, box_collider1->true_bottom };
		vector2float box_collider1_p3 = { box_collider1->true_right, box_collider1->true_bottom };

		vector2float box_collider1_border_point;

		// Check top side
		vector2float box_collider1_border_point_top = AzurMath::find_point_x(collider0_point, collider1_point, box_collider1->true_top);
		if (box_collider1_border_point_top.x > box_collider1->true_left || box_collider1_border_point_top.x < box_collider1->true_right)
		{
			collider1_border_point = box_collider1_border_point_top;
		}
		// Check right side
		vector2float box_collider1_border_point_right = AzurMath::find_point_y(collider0_point, collider1_point, box_collider1->true_right);
		if (box_collider1_border_point_right.y < box_collider1->true_top || box_collider1_border_point_right.y < box_collider1->true_bottom)
		{
			collider1_border_point = box_collider1_border_point_right;
		}
		// Check bottom side
		vector2float box_collider1_border_point_bottom = AzurMath::find_point_x(collider0_point, collider1_point, box_collider1->true_bottom);
		if (box_collider1_border_point_bottom.x > box_collider1->true_left || box_collider1_border_point_bottom.x < box_collider1->true_right)
		{
			collider1_border_point = box_collider1_border_point_bottom;
		}
		// Check bottom left
		vector2float box_collider1_border_point_left = AzurMath::find_point_y(collider0_point, collider1_point, box_collider1->true_left);
		if (box_collider1_border_point_left.y < box_collider1->true_top || box_collider1_border_point_left.y > box_collider1->true_right)
		{
			collider1_border_point = box_collider1_border_point_left;
		}
	}

	return std::make_pair(collider0_border_point, collider1_border_point);
}