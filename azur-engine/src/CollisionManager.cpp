#include "CollisionManager.h"

std::vector<Collider*> CollisionManager::colliders;

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
		// WARNING: TODO: The moment a CircleColliderComponent is added to vector of colliders, everything breaks.
		Collider* collider0 = colliders[i];
		// We don't need to evaluate collisions for inactie entities
		if (!collider0->entity->active) continue;


		for (size_t j = i + 1; j < colliders.size(); ++j)
		{
			// TODO: Test BoxColliders agains Circle Colliders.
			Collider* collider1 = colliders[j];
			// We don't need to evaluate collisions for inactie entities
			if (!collider1->entity->active) continue;


			// Box with Box Collision
			if (collider0->type == ColliderType::BOX && collider1->type == ColliderType::BOX)
			{
				BoxCollider* box_collider0 = (BoxCollider*)collider0;
				BoxCollider* box_collider1 = (BoxCollider*)collider1;
				bool is_colliding = box_collider0->get_true_top() < box_collider1->get_true_bottom() && box_collider0->get_true_left() < box_collider1->get_true_right() &&
					box_collider1->get_true_top() < box_collider0->get_true_bottom() && box_collider1->get_true_left() < box_collider0->get_true_right();
				if (is_colliding)
				{
					set_collision_status(collider0, collider1);
				}
			}
			else if (collider0->type == ColliderType::CIRCLE && collider1->type == ColliderType::CIRCLE)
			{
				CircleCollider* circle_collider0 = (CircleCollider*)collider0;
				CircleCollider* circle_collider1 = (CircleCollider*)collider1;
				vector2float collider0_point = { circle_collider0->position->x , circle_collider0->position->y };
				vector2float collider1_point = { circle_collider1->position->x , circle_collider1->position->y };

				float d0 = AzurMath::find_distance_between_points(collider0_point, collider1_point);
				float d1 = AzurMath::find_distance_between_points(collider1_point, collider0_point);
				float distance = d0 > d1 ? d1 : d0;
				float diameter = circle_collider0->radius + circle_collider1->radius;
				bool is_colliding = distance < diameter;
				if (is_colliding)
				{
					set_collision_status(collider0, collider1);
				}
			}
			else if (collider0->type == ColliderType::CIRCLE && collider1->type == ColliderType::BOX ||
					 collider0->type == ColliderType::BOX && collider1->type == ColliderType::CIRCLE)
			{
					vector2float collision_point = {};
					CircleCollider* circle_collider = collider0->type == ColliderType::CIRCLE ? (CircleCollider*)collider0 : (CircleCollider*)collider1;
					BoxCollider* box_collider = collider0->type == ColliderType::BOX ? (BoxCollider*)collider0 : (BoxCollider*)collider1;

					float box_true_top = box_collider->get_true_top();
					float box_true_right = box_collider->get_true_right();
					float box_true_bottom = box_collider->get_true_bottom();
					float box_true_left = box_collider->get_true_left();

					float circle_pos_x = circle_collider->position->x;
					float circle_pos_y = circle_collider->position->y;

					if (box_true_top <= circle_pos_y && box_true_bottom >= circle_pos_y &&
						box_collider->position->x >= circle_pos_x)
					{
						collision_point.x = box_true_left;
						collision_point.y = circle_pos_y;
					}
					else if (box_true_top <= circle_pos_y&& box_true_bottom >= circle_pos_y&&
						box_collider->position->x <= circle_pos_x)
					{
						collision_point.x = box_true_right;
						collision_point.y = circle_pos_y;
					}
					else if (box_true_left <= circle_pos_x && box_true_right >= circle_pos_x &&
						box_collider->position->y >= circle_pos_y)
					{
						collision_point.x = circle_pos_x;
						collision_point.y = box_true_top;
					}
					else if (box_true_left <= circle_pos_x && box_true_right >= circle_pos_x &&
						box_collider->position->y <= circle_pos_y)
					{
						collision_point.x = circle_pos_x;
						collision_point.y = box_true_bottom;
					}
					// top left
					else if (box_true_bottom <= circle_pos_y && box_true_right <= circle_pos_x)
					{
						collision_point.x = box_true_right;
						collision_point.y = box_true_bottom;
					}
					// top right
					else if (box_true_bottom <= circle_pos_y && box_true_left >= circle_pos_x)
					{
						collision_point.x = box_true_left;
						collision_point.y = box_true_bottom;
					}
					// bottom left
					else if (box_true_top >= circle_pos_y && box_true_right <= circle_pos_x)
					{
						collision_point.x = box_true_right;
						collision_point.y = box_true_top;
					}
					// bottom right
					else if (box_true_top >= circle_pos_y && box_true_left >= circle_pos_x)
					{
						collision_point.x = box_true_left;
						collision_point.y = box_true_top;
					}



					vector2float circle_pos_vector = { circle_pos_x , circle_pos_y };
					float d0 = AzurMath::find_distance_between_points(circle_pos_vector, collision_point);
					float d1 = AzurMath::find_distance_between_points(collision_point, circle_pos_vector);
					float distance = d0 > d1 ? d1 : d0;
					float radius = circle_collider->radius;
					bool is_colliding = distance < radius ||
						circle_pos_x >= box_true_left && circle_pos_x <= box_true_right &&
						circle_pos_y <= box_true_bottom && circle_pos_x >= box_true_top;
					if (is_colliding)
					{
						set_collision_status(collider0, collider1);
					}
			}
		}
	}
}

void CollisionManager::Draw(SDL_Renderer* renderer)
{

}

void CollisionManager::AddCollider(Collider* collider)
{
	colliders.push_back(collider);
}

void CollisionManager::RemoveCollider(Collider* collider)
{
	std::vector<Collider*>::iterator pos = std::find(colliders.begin(), colliders.end(), collider);
	if (pos != colliders.end())
	{
		colliders.erase(pos);
	}
}

// TODO: NOT BEING USED. CHECK IF RELEVANT
// returns an array of two points with the two closest points of first and second collider, respectively
std::pair<vector2float, vector2float> CollisionManager::find_closest_collision_border_point(Collider* collider0, Collider* collider1)
{
	vector2float collider0_border_point = {};
	vector2float collider1_border_point = {};
	// Get a linear function going from one collider to the other
	vector2float collider0_point = { collider0->position->x, collider0->position->y };
	vector2float collider1_point = { collider1->position->x, collider1->position->y };

	// Collider0
	if (collider0->type == ColliderType::BOX)
	{
		BoxCollider* box_collider0 = (BoxCollider*)collider0;
		vector2float box_collider0_p0 = { box_collider0->get_true_left(),  box_collider0->get_true_top() };
		vector2float box_collider0_p1 = { box_collider0->get_true_right(), box_collider0->get_true_top() };
		vector2float box_collider0_p2 = { box_collider0->get_true_left(),  box_collider0->get_true_bottom() };
		vector2float box_collider0_p3 = { box_collider0->get_true_right(), box_collider0->get_true_bottom() };

		// Check top side
		vector2float box_collider0_border_point_top = AzurMath::find_point_x(collider0_point, collider1_point, box_collider0->get_true_top());
		if (box_collider0_border_point_top.x > box_collider0->get_true_left() || box_collider0_border_point_top.x < box_collider0->get_true_right())
		{
			collider0_border_point = box_collider0_border_point_top;
		}
		// Check right side
		vector2float box_collider0_border_point_right = AzurMath::find_point_y(collider0_point, collider1_point, box_collider0->get_true_right());
		if (box_collider0_border_point_right.y < box_collider0->get_true_top() || box_collider0_border_point_right.y < box_collider0->get_true_bottom())
		{
			collider0_border_point = box_collider0_border_point_right;
		}
		// Check bottom side
		vector2float box_collider0_border_point_bottom = AzurMath::find_point_x(collider0_point, collider1_point, box_collider0->get_true_bottom());
		if (box_collider0_border_point_bottom.x > box_collider0->get_true_left() || box_collider0_border_point_bottom.x < box_collider0->get_true_right())
		{
			collider0_border_point = box_collider0_border_point_bottom;
		}
		// Check bottom left
		vector2float box_collider0_border_point_left = AzurMath::find_point_y(collider0_point, collider1_point, box_collider0->get_true_left());
		if (box_collider0_border_point_left.y < box_collider0->get_true_top() || box_collider0_border_point_left.y > box_collider0->get_true_right())
		{
			collider0_border_point = box_collider0_border_point_left;
		}
	}
	// Collider1
	if (collider1->type == ColliderType::BOX)
	{
		BoxCollider* box_collider1 = (BoxCollider*)collider1;
		vector2float box_collider1_p0 = { box_collider1->get_true_left(),  box_collider1->get_true_top() };
		vector2float box_collider1_p1 = { box_collider1->get_true_right(), box_collider1->get_true_top() };
		vector2float box_collider1_p2 = { box_collider1->get_true_left(),  box_collider1->get_true_bottom() };
		vector2float box_collider1_p3 = { box_collider1->get_true_right(), box_collider1->get_true_bottom() };

		// Check top side
		vector2float box_collider1_border_point_top = AzurMath::find_point_x(collider0_point, collider1_point, box_collider1->get_true_top());
		if (box_collider1_border_point_top.x > box_collider1->get_true_left() || box_collider1_border_point_top.x < box_collider1->get_true_right())
		{
			collider1_border_point = box_collider1_border_point_top;
		}
		// Check right side
		vector2float box_collider1_border_point_right = AzurMath::find_point_y(collider0_point, collider1_point, box_collider1->get_true_right());
		if (box_collider1_border_point_right.y < box_collider1->get_true_top() || box_collider1_border_point_right.y < box_collider1->get_true_bottom())
		{
			collider1_border_point = box_collider1_border_point_right;
		}
		// Check bottom side
		vector2float box_collider1_border_point_bottom = AzurMath::find_point_x(collider0_point, collider1_point, box_collider1->get_true_bottom());
		if (box_collider1_border_point_bottom.x > box_collider1->get_true_left() || box_collider1_border_point_bottom.x < box_collider1->get_true_right())
		{
			collider1_border_point = box_collider1_border_point_bottom;
		}
		// Check bottom left
		vector2float box_collider1_border_point_left = AzurMath::find_point_y(collider0_point, collider1_point, box_collider1->get_true_left());
		if (box_collider1_border_point_left.y < box_collider1->get_true_top() || box_collider1_border_point_left.y > box_collider1->get_true_right())
		{
			collider1_border_point = box_collider1_border_point_left;
		}
	}

	return std::make_pair(collider0_border_point, collider1_border_point);
}

void CollisionManager::set_collision_status(Collider* collider0, Collider* collider1)
{
	collider0->isColliding = true;
	collider1->isColliding = true;
	collider0->collider_references.push_back(collider1);
	collider1->collider_references.push_back(collider0);
	bool add_tag_0 = true;
	bool add_tag_1 = true;
	for (size_t k = 0; k < collider0->collider_tags.size(); ++k)
	{
		if (collider0->collider_tags[k] == collider1->entity->tag)
		{
			add_tag_0 = false;
			break;
		}
	}
	for (size_t k = 0; k < collider1->collider_tags.size(); ++k)
	{
		if (collider1->collider_tags[k] == collider0->entity->tag)
		{
			add_tag_1 = false;
			break;
		}
	}
	if (add_tag_0) collider0->collider_tags.push_back(collider1->entity->tag);
	if (add_tag_1) collider1->collider_tags.push_back(collider0->entity->tag);
}
