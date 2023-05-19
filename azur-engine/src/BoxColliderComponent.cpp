#include "BoxColliderComponent.h"

#include "vector2float.h"
#include "CollisionManager.h"

#include "EntityTag.h"

void BoxColliderComponent::draw(SDL_Renderer* renderer)
{
	// drawing points
	vector2float p0{ true_left,  true_top };
	vector2float p1{ true_right, true_top };
	vector2float p2{ true_left,  true_bottom };
	vector2float p3{ true_right, true_bottom };

#ifdef _DEBUG
	// This is a debug drawing of the collision box.
	if (isColliding) SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // red
	else SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // green
	SDL_RenderDrawLine(renderer, p0.x, p0.y, p1.x, p1.y);
	SDL_RenderDrawLine(renderer, p1.x, p1.y, p3.x, p3.y);
	SDL_RenderDrawLine(renderer, p2.x, p2.y, p0.x, p0.y);
	SDL_RenderDrawLine(renderer, p3.x, p3.y, p2.x, p2.y);
#endif
}

void BoxColliderComponent::update()
{
	true_top = position->y + offset_top;
	true_right = position->x + offset_right;
	true_bottom = position->y + offset_bottom;
	true_left = position->x + offset_left;
}

void BoxColliderComponent::init()
{
	position = entity->getComponent<PositionComponent>();

	// test value. Default should be 0. The actual values are set outside of this function.
	offset_top = 0;
	offset_right = 0;
	offset_bottom = 0;
	offset_left = 0;

	true_top = 0;
	true_right = 0;
	true_bottom = 0;
	true_left = 0;

	collisionTagName = EntityTag::UNDEFINED;
	isColliding = false;

	collision_references = {};
	collision_tags = {};

	CollisionManager::AddCollider(this);
}

BoxColliderComponent::~BoxColliderComponent()
{
	CollisionManager::RemoveCollider(this);
}
