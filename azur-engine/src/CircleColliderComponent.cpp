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
	int32_t centerX = (int32_t)position->x;
	int32_t centerY = (int32_t)position->y;
	const int32_t diameter = int32_t(radius * 2.0f);

	int32_t x = int32_t(radius - 1);
	int32_t y = 0;
	int32_t tx = 1;
	int32_t ty = 1;
	int32_t error = (tx - diameter);

	while (x >= y)
	{
		SDL_RenderDrawPoint(renderer, int(position->x + x), int(position->y - y));
		SDL_RenderDrawPoint(renderer, int(position->x + x), int(position->y + y));
		SDL_RenderDrawPoint(renderer, int(position->x - x), int(position->y - y));
		SDL_RenderDrawPoint(renderer, int(position->x - x), int(position->y + y));
		SDL_RenderDrawPoint(renderer, int(position->x + y), int(position->y - x));
		SDL_RenderDrawPoint(renderer, int(position->x + y), int(position->y + x));
		SDL_RenderDrawPoint(renderer, int(position->x - y), int(position->y - x));
		SDL_RenderDrawPoint(renderer, int(position->x - y), int(position->y + x));
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
