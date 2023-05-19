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
#ifdef _DEBUG
	if (isColliding) SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // red
	else SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // green

	// DEBUG: Draw circle for testing
	int32_t centerX = position->x;
	int32_t centerY = position->y;
	const int32_t diameter = (radius * 2);

	int32_t x = (radius - 1);
	int32_t y = 0;
	int32_t tx = 1;
	int32_t ty = 1;
	int32_t error = (tx - diameter);

	while (x >= y)
	{
		SDL_RenderDrawPoint(renderer, position->x + x, position->y - y);
		SDL_RenderDrawPoint(renderer, position->x + x, position->y + y);
		SDL_RenderDrawPoint(renderer, position->x - x, position->y - y);
		SDL_RenderDrawPoint(renderer, position->x - x, position->y + y);
		SDL_RenderDrawPoint(renderer, position->x + y, position->y - x);
		SDL_RenderDrawPoint(renderer, position->x + y, position->y + x);
		SDL_RenderDrawPoint(renderer, position->x - y, position->y - x);
		SDL_RenderDrawPoint(renderer, position->x - y, position->y + x);
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
#endif
}
