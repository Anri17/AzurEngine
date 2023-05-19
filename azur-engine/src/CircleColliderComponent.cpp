#include "CircleColliderComponent.h"

void CircleColliderComponent::init()
{
	ColliderComponent::init();
	type = ColliderType::CIRCLE;

	// Default Radius Value. True value is set outside this method.
	radius = 1.0f;
}

void CircleColliderComponent::update()
{

}

void CircleColliderComponent::draw(SDL_Renderer* renderer)
{

}
