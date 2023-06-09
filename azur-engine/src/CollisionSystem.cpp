#include "CollisionSystem.h"

#include "AzurDebug.h"
#include "Application.h"

CollisionSystem::CollisionSystem()
{
	Application::systems.push_back(this);
	entities = ECS::Manager::GetEntitiesVector();
}

void CollisionSystem::Init()
{
	ComponentID positionID = ECS::GetComponentTypeID<Position>();
	ComponentID colliderID = ECS::GetComponentTypeID<Collider>();

	systemBitset[positionID] = true;
	systemBitset[colliderID] = true;
}

void CollisionSystem::Update()
{
	// Check every collision for overlap
	// If they overlap, change their state.

	// Reset Collider Data First
	for (size_t i = 0; i < entities->size(); ++i)
	{
		Entity* entity = entities->at(i);
		if (!entity->active) continue;
		if (!((entity->HasComponent<BoxCollider>() || entity->HasComponent<CircleCollider>())
			&& entity->HasComponent<Position>()))
		{
			continue;
		}
		Collider* collider = nullptr;
		if (entity->HasComponent<BoxCollider>()) collider = entity->GetComponent<BoxCollider>();
		if (entity->HasComponent<CircleCollider>()) collider = entity->GetComponent<CircleCollider>();

		collider->isColliding = false;
		size_t reference_total = collider->collider_references.size();
		size_t tag_total = collider->collider_tags.size();
		for (size_t j = 0; j < reference_total; ++j)
			collider->collider_references.pop_back();
		for (size_t j = 0; j < tag_total; ++j)
			collider->collider_tags.pop_back();
	}

	// Check for Collisions and set the respective data for each collider
	for (size_t i = 0; i < entities->size(); ++i)
	{
		// Check if entity is collider or not or if it's not active. Get the position and proper collider.
		Entity* entity0 = entities->at(i);
		if (!entity0->active) continue;
		if (!((entity0->HasComponent<BoxCollider>() || entity0->HasComponent<CircleCollider>())
			&& entity0->HasComponent<Position>()))
		{
			continue;
		}



		for (size_t j = i + 1; j < entities->size(); ++j)
		{
			// Check if entity is collider or not or if it's not active. Get the position and proper collider.
			Entity* entity1 = entities->at(j);
			if (!entity1->active) continue;
			if (!((entity1->HasComponent<BoxCollider>() || entity1->HasComponent<CircleCollider>())
				&& entity1->HasComponent<Position>()))
			{
				continue;
			}


			// Box with Box Collision
			if (entity0->HasComponent<BoxCollider>() && entity1->HasComponent<BoxCollider>())
			{
				BoxCollider* box_collider0 = entity0->GetComponent<BoxCollider>();
				Position* box_position0 = entity0->GetComponent<Position>();
				BoxCollider* box_collider1 = entity1->GetComponent<BoxCollider>();
				Position* box_position1 = entity1->GetComponent<Position>();

				bool is_colliding = box_collider0->get_true_top(box_position0) < box_collider1->get_true_bottom(box_position1) &&
									box_collider0->get_true_left(box_position0) < box_collider1->get_true_right(box_position1) &&
									box_collider1->get_true_top(box_position1) < box_collider0->get_true_bottom(box_position0) &&
									box_collider1->get_true_left(box_position1) < box_collider0->get_true_right(box_position0);
				if (is_colliding)
				{
					set_collision_status(box_collider0, box_collider1);
				}
			}
			else if (entity0->HasComponent<CircleCollider>() && entity1->HasComponent<CircleCollider>())
			{
				CircleCollider* circle_collider0 = entity0->GetComponent<CircleCollider>();
				Position* circle_position0 = entity0->GetComponent<Position>();
				CircleCollider* circle_collider1 = entity1->GetComponent<CircleCollider>();
				Position* circle_position1 = entity1->GetComponent<Position>();
				vector2float collider0_point = { circle_position0->x , circle_position0->y };
				vector2float collider1_point = { circle_position1->x , circle_position1->y };

				float d0 = AzurMath::find_distance_between_points(collider0_point, collider1_point);
				float d1 = AzurMath::find_distance_between_points(collider1_point, collider0_point);
				float distance = d0 > d1 ? d1 : d0;
				float diameter = circle_collider0->radius + circle_collider1->radius;
				bool is_colliding = distance < diameter;
				if (is_colliding)
				{
					set_collision_status(circle_collider0, circle_collider1);
				}
			}
			else if (entity0->HasComponent<CircleCollider>() && entity1->HasComponent<BoxCollider>()||
					 entity0->HasComponent<BoxCollider>()    && entity1->HasComponent<CircleCollider>())
			{
				vector2float collision_point = {};
				CircleCollider* circle_collider;
				Position* circle_position;
				BoxCollider* box_collider;
				Position* box_position;
				if (entity0->HasComponent<CircleCollider>())
				{
					circle_position = entity0->GetComponent<Position>();
					circle_collider = (CircleCollider*)entity0->GetComponent<CircleCollider>();
				}
				else
				{
					circle_position = entity1->GetComponent<Position>();
					circle_collider = (CircleCollider*)entity1->GetComponent<CircleCollider>();
				}
				if (entity1->HasComponent<BoxCollider>())
				{
					box_position = entity1->GetComponent<Position>();
					box_collider = (BoxCollider*)entity1->GetComponent<BoxCollider>();
				}
				else
				{
					box_position = entity0->GetComponent<Position>();
					box_collider = (BoxCollider*)entity0->GetComponent<BoxCollider>();
				}

				float box_true_top    = box_collider->get_true_top(box_position);
				float box_true_right  = box_collider->get_true_right(box_position);
				float box_true_bottom = box_collider->get_true_bottom(box_position);
				float box_true_left   = box_collider->get_true_left(box_position);

				float circle_pos_x = circle_position->x;
				float circle_pos_y = circle_position->y;

				if (box_true_top <= circle_pos_y && box_true_bottom >= circle_pos_y &&
					box_position->x >= circle_pos_x)
				{
					collision_point.x = box_true_left;
					collision_point.y = circle_pos_y;
				}
				else if (box_true_top <= circle_pos_y && box_true_bottom >= circle_pos_y &&
					box_position->x <= circle_pos_x)
				{
					collision_point.x = box_true_right;
					collision_point.y = circle_pos_y;
				}
				else if (box_true_left <= circle_pos_x && box_true_right >= circle_pos_x &&
					box_position->y >= circle_pos_y)
				{
					collision_point.x = circle_pos_x;
					collision_point.y = box_true_top;
				}
				else if (box_true_left <= circle_pos_x && box_true_right >= circle_pos_x &&
					box_position->y <= circle_pos_y)
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
					set_collision_status(circle_collider, box_collider);
				}
			}
		}
	}
}

void CollisionSystem::Render(SDL_Renderer* renderer)
{
	if (AzurDebug::debug_mode)
	{
		for (Entity* e : (*entities))
		{
			// Check if entity is collider or not or if it's not active. Get the position and proper collider.
			if (!e->active) continue;
			if (!((e->HasComponent<BoxCollider>() || e->HasComponent<CircleCollider>())
				&& e->HasComponent<Position>()))
			{
				continue;
			}
			Collider* collider = (Collider*)e->GetComponent<BoxCollider>();
			collider = collider ? collider : (Collider*)e->GetComponent<CircleCollider>();

			if (collider->type == ColliderType::BOX)
			{
				BoxCollider* box_collider = e->GetComponent<BoxCollider>();
				Position* box_position = e->GetComponent<Position>();

				// drawing points
				vector2int p0{ Application::GetWindowTrueX(box_collider->get_true_left(box_position)), Application::GetWindowTrueY(box_collider->get_true_top(box_position)) };
				vector2int p1{ Application::GetWindowTrueX(box_collider->get_true_right(box_position)), Application::GetWindowTrueY(box_collider->get_true_top(box_position)) };
				vector2int p2{ Application::GetWindowTrueX(box_collider->get_true_left(box_position)), Application::GetWindowTrueY(box_collider->get_true_bottom(box_position)) };
				vector2int p3{ Application::GetWindowTrueX(box_collider->get_true_right(box_position)), Application::GetWindowTrueY(box_collider->get_true_bottom(box_position)) };

				// This is a debug drawing of the collision box.
				// Not need to show playfield collision. That would be red all the time and would make this whole code useless
				if (box_collider->entity->tag == ECS::Tag::PLAYFIELD)
				{
					// Playfield is blue to distinguish from other colliders
					SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); // blue
				}
				else if (box_collider->collider_tags.size() == 1 && box_collider->collider_tags[0] == ECS::Tag::PLAYFIELD)
				{
					SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // green
				}
				else if (box_collider->isColliding)
				{
					SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // red
				}
				else
				{
					SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // green
				}

				SDL_RenderDrawLine(renderer, p0.x, p0.y, p1.x, p1.y);
				SDL_RenderDrawLine(renderer, p1.x, p1.y, p3.x, p3.y);
				SDL_RenderDrawLine(renderer, p2.x, p2.y, p0.x, p0.y);
				SDL_RenderDrawLine(renderer, p3.x, p3.y, p2.x, p2.y);
			}

			if (collider->type == ColliderType::CIRCLE)
			{
				CircleCollider* circle_collider = e->GetComponent<CircleCollider>();
				Position* position = e->GetComponent<Position>();

				// Not need to show playfield collision. That would be red all the time and would make this whole code useless
				if (circle_collider->entity->tag == ECS::Tag::PLAYFIELD)
				{
					// Playfield is blue to distinguish from other colliders
					SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); // blue
				}
				else if (circle_collider->collider_tags.size() == 1 && circle_collider->collider_tags[0] == ECS::Tag::PLAYFIELD)
				{
					SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // green
				}
				else if (circle_collider->isColliding)
				{
					SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // red
				}
				else
				{
					SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // green
				}

				// DEBUG: Draw circle for testing
				int32_t centerX = (int32_t)position->x;
				int32_t centerY = (int32_t)position->y;
				const int32_t diameter = int32_t(circle_collider->radius * 2.0f);

				int32_t x = int32_t(circle_collider->radius - 1);
				int32_t y = 0;
				int32_t tx = 1;
				int32_t ty = 1;
				int32_t error = (tx - diameter);

				while (x >= y)
				{
					SDL_RenderDrawPoint(renderer, Application::GetWindowTrueX(position->x + x), Application::GetWindowTrueY(position->y - y));
					SDL_RenderDrawPoint(renderer, Application::GetWindowTrueX(position->x + x), Application::GetWindowTrueY(position->y + y));
					SDL_RenderDrawPoint(renderer, Application::GetWindowTrueX(position->x - x), Application::GetWindowTrueY(position->y - y));
					SDL_RenderDrawPoint(renderer, Application::GetWindowTrueX(position->x - x), Application::GetWindowTrueY(position->y + y));
					SDL_RenderDrawPoint(renderer, Application::GetWindowTrueX(position->x + y), Application::GetWindowTrueY(position->y - x));
					SDL_RenderDrawPoint(renderer, Application::GetWindowTrueX(position->x + y), Application::GetWindowTrueY(position->y + x));
					SDL_RenderDrawPoint(renderer, Application::GetWindowTrueX(position->x - y), Application::GetWindowTrueY(position->y - x));
					SDL_RenderDrawPoint(renderer, Application::GetWindowTrueX(position->x - y), Application::GetWindowTrueY(position->y + x));
					if (error <= 0)
					{
						++y;
						error += ty;
						ty += 2;
					}
					if (error > 0)
					{
						--x;
						tx += 2;
						error += (tx - diameter);
					}
				}
			}
		}
	}
}

void CollisionSystem::set_collision_status(Collider* collider0, Collider* collider1)
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
