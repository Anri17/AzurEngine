#include "CollisionSystem.h"

#include "./../AzurDebug.h"
#include "./../Application.h"

CollisionSystem::CollisionSystem()
{
	AzurEngine::Application::systems.push_back(this);
	entities = ECS::ECSManager::get_entities_vector();
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
	// Variables: Reset Collider Data First
	size_t   i, j;
	size_t   collider_reference_total_count;
	size_t   collider_tag_total_count;
	size_t   entity_total_count;
	Entity   *entity = nullptr;
	Collider *collider = nullptr;

	// Check every collision for overlap and change their state respectively

	// Reset Collider Data First
	entity_total_count = entities->size();
	for (i = 0; i < entity_total_count; ++i) {
		entity = entities->at(i);
		if (!entity->active ||
			!(entity->HasComponent<BoxCollider>() ||
			  entity->HasComponent<CircleCollider>()) ||
			!entity->HasComponent<Position>()) {
			continue;
		}
		if (entity->HasComponent<BoxCollider>()) {
			collider = entity->GetComponent<BoxCollider>();
		}
		if (entity->HasComponent<CircleCollider>()) {
			collider = entity->GetComponent<CircleCollider>();
		}
		collider->isColliding = false;
		collider_reference_total_count = collider->collider_references.size();
		collider_tag_total_count = collider->collider_tags.size();
		for (j = 0; j < collider_reference_total_count; ++j) {
			collider->collider_references.pop_back();
		}
		for (j = 0; j < collider_tag_total_count; ++j) {
			collider->collider_tags.pop_back();
		}
	}

	// variables
	Entity *entity0;
	Entity *entity1;

	// Check for Collisions and set the respective data for each collider
	for (i = 0; i < entity_total_count; ++i) {
		// Check if entity is collider or not or if it's not active. Get the position and proper collider.
		entity0 = entities->at(i);
		if (!entity0->active ||
			(!entity0->HasComponent<BoxCollider>() &&
			 !entity0->HasComponent<CircleCollider>()) ||
			!entity0->HasComponent<Position>()) {
			continue;
		}

		for (j = i + 1; j < entities->size(); ++j) {
			// Check if entity is collider or not or if it's not active. Get the position and proper collider.
			entity1 = entities->at(j);
			if (!entity1->active ||
				(!entity1->HasComponent<BoxCollider>() &&
				 !entity1->HasComponent<CircleCollider>()) ||
				!entity1->HasComponent<Position>()) {
				continue;
			}

			// Box with Box Collision
			if (entity0->HasComponent<BoxCollider>() && entity1->HasComponent<BoxCollider>()) {
				BoxCollider *box_a_collider, *box_b_collider;
				Position    *box_a_position, *box_b_position;
				bool        is_overlapping;

				box_a_collider = entity0->GetComponent<BoxCollider>();
				box_b_collider = entity1->GetComponent<BoxCollider>();
				box_a_position = entity0->GetComponent<Position>();
				box_b_position = entity1->GetComponent<Position>();
				is_overlapping = box_a_collider->get_true_top(box_a_position)  < box_b_collider->get_true_bottom(box_b_position) &&
				                 box_a_collider->get_true_left(box_a_position) < box_b_collider->get_true_right(box_b_position)  &&
				                 box_b_collider->get_true_top(box_b_position)  < box_a_collider->get_true_bottom(box_a_position) &&
				                 box_b_collider->get_true_left(box_b_position) < box_a_collider->get_true_right(box_a_position);
				
				if (is_overlapping) {
					set_collision_status(box_a_collider, box_b_collider);
				}
			}
			else if (entity0->HasComponent<CircleCollider>() &&
					 entity1->HasComponent<CircleCollider>()) {
				CircleCollider *circle_collider0;
				Position       *circle_position0;
				CircleCollider *circle_collider1;
				Position       *circle_position1;
				vector2float   collider0_point;
				vector2float   collider1_point;
				float          d0;
				float          d1;
				float          distance;
				float          diameter;
				bool           is_colliding;

				circle_collider0 = entity0->GetComponent<CircleCollider>();
				circle_position0 = entity0->GetComponent<Position>();
				circle_collider1 = entity1->GetComponent<CircleCollider>();
				circle_position1 = entity1->GetComponent<Position>();
				collider0_point  = { circle_position0->x , circle_position0->y };
				collider1_point  = { circle_position1->x , circle_position1->y };
				
				d0 = AzurMath::find_distance_between_points(collider0_point, collider1_point);
				d1 = AzurMath::find_distance_between_points(collider1_point, collider0_point);
				distance = d0 > d1 ? d1 : d0;
				diameter = circle_collider0->radius + circle_collider1->radius;
				is_colliding = distance < diameter;
				if (is_colliding) {
					set_collision_status(circle_collider0, circle_collider1);
				}
			}
			else if (entity0->HasComponent<CircleCollider>() && entity1->HasComponent<BoxCollider>() ||
					 entity0->HasComponent<BoxCollider>()    && entity1->HasComponent<CircleCollider>()) {
				vector2float   collision_point;
				CircleCollider *circle_collider;
				Position       *circle_position;
				BoxCollider    *box_collider;
				Position       *box_position;
				float          box_true_top;
				float          box_true_right;
				float          box_true_bottom;
				float          box_true_left;

				float circle_pos_x;
				float circle_pos_y;

				if (entity0->HasComponent<CircleCollider>()) {
					circle_position = entity0->GetComponent<Position>();
					circle_collider = (CircleCollider*)entity0->GetComponent<CircleCollider>();
				}
				else {
					circle_position = entity1->GetComponent<Position>();
					circle_collider = (CircleCollider*)entity1->GetComponent<CircleCollider>();
				}
				if (entity1->HasComponent<BoxCollider>()) {
					box_position = entity1->GetComponent<Position>();
					box_collider = (BoxCollider*)entity1->GetComponent<BoxCollider>();
				}
				else {
					box_position = entity0->GetComponent<Position>();
					box_collider = (BoxCollider*)entity0->GetComponent<BoxCollider>();
				}

				box_true_top    = box_collider->get_true_top(box_position);
				box_true_right  = box_collider->get_true_right(box_position);
				box_true_bottom = box_collider->get_true_bottom(box_position);
				box_true_left   = box_collider->get_true_left(box_position);

				circle_pos_x = circle_position->x;
				circle_pos_y = circle_position->y;

				if (box_true_top <= circle_pos_y &&
					box_true_bottom >= circle_pos_y &&
					box_position->x >= circle_pos_x) {
					collision_point.x = box_true_left;
					collision_point.y = circle_pos_y;
				} else if (box_true_top    <= circle_pos_y &&
						   box_true_bottom >= circle_pos_y &&
						   box_position->x <= circle_pos_x) {
					collision_point.x = box_true_right;
					collision_point.y = circle_pos_y;
				} else if (box_true_left   <= circle_pos_x &&
						   box_true_right  >= circle_pos_x &&
					       box_position->y >= circle_pos_y) {
					collision_point.x = circle_pos_x;
					collision_point.y = box_true_top;
				} else if (box_true_left <= circle_pos_x &&
						   box_true_right >= circle_pos_x &&
						   box_position->y <= circle_pos_y) {
					collision_point.x = circle_pos_x;
					collision_point.y = box_true_bottom;
				} else if (box_true_bottom <= circle_pos_y &&
						 box_true_right <= circle_pos_x) { // top left
					collision_point.x = box_true_right;
					collision_point.y = box_true_bottom;
				} else if (box_true_bottom <= circle_pos_y &&
						   box_true_left >= circle_pos_x) { // top right
					collision_point.x = box_true_left;
					collision_point.y = box_true_bottom;
				} else if (box_true_top >= circle_pos_y &&
						   box_true_right <= circle_pos_x) { // bottom left
					collision_point.x = box_true_right;
					collision_point.y = box_true_top;
				} else if (box_true_top >= circle_pos_y &&
						   box_true_left >= circle_pos_x) { // bottom right
					collision_point.x = box_true_left;
					collision_point.y = box_true_top;
				}

				vector2float circle_pos_vector;
				float        d0;
				float        d1;
				float        distance;
				float        radius;
				bool         is_colliding;

				circle_pos_vector.x = circle_pos_x;
				circle_pos_vector.y = circle_pos_y;
				d0 = AzurMath::find_distance_between_points(circle_pos_vector, collision_point);
				d1 = AzurMath::find_distance_between_points(collision_point, circle_pos_vector);
				distance = d0 > d1 ? d1 : d0;
				radius = circle_collider->radius;

				is_colliding = distance < radius ||
				               circle_pos_x >= box_true_left && circle_pos_x <= box_true_right &&
				               circle_pos_y <= box_true_bottom && circle_pos_x >= box_true_top;
				if (is_colliding) {
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
				vector2int p0{ AzurEngine::Application::GetWindowTrueX(box_collider->get_true_left(box_position)), AzurEngine::Application::GetWindowTrueY(box_collider->get_true_top(box_position)) };
				vector2int p1{ AzurEngine::Application::GetWindowTrueX(box_collider->get_true_right(box_position)), AzurEngine::Application::GetWindowTrueY(box_collider->get_true_top(box_position)) };
				vector2int p2{ AzurEngine::Application::GetWindowTrueX(box_collider->get_true_left(box_position)), AzurEngine::Application::GetWindowTrueY(box_collider->get_true_bottom(box_position)) };
				vector2int p3{ AzurEngine::Application::GetWindowTrueX(box_collider->get_true_right(box_position)), AzurEngine::Application::GetWindowTrueY(box_collider->get_true_bottom(box_position)) };

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
					SDL_RenderDrawPoint(renderer, AzurEngine::Application::GetWindowTrueX(position->x + x), AzurEngine::Application::GetWindowTrueY(position->y - y));
					SDL_RenderDrawPoint(renderer, AzurEngine::Application::GetWindowTrueX(position->x + x), AzurEngine::Application::GetWindowTrueY(position->y + y));
					SDL_RenderDrawPoint(renderer, AzurEngine::Application::GetWindowTrueX(position->x - x), AzurEngine::Application::GetWindowTrueY(position->y - y));
					SDL_RenderDrawPoint(renderer, AzurEngine::Application::GetWindowTrueX(position->x - x), AzurEngine::Application::GetWindowTrueY(position->y + y));
					SDL_RenderDrawPoint(renderer, AzurEngine::Application::GetWindowTrueX(position->x + y), AzurEngine::Application::GetWindowTrueY(position->y - x));
					SDL_RenderDrawPoint(renderer, AzurEngine::Application::GetWindowTrueX(position->x + y), AzurEngine::Application::GetWindowTrueY(position->y + x));
					SDL_RenderDrawPoint(renderer, AzurEngine::Application::GetWindowTrueX(position->x - y), AzurEngine::Application::GetWindowTrueY(position->y - x));
					SDL_RenderDrawPoint(renderer, AzurEngine::Application::GetWindowTrueX(position->x - y), AzurEngine::Application::GetWindowTrueY(position->y + x));
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
