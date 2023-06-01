#include "CircleCollider.h"


#include ".\..\..\Application.h"
#include ".\..\..\AzurLib.h"
#include ".\..\..\AzurDebug.h"
#include ".\..\ECS_Tag.h"
namespace ECS
{
	void CircleCollider::init()
	{
		Collider::init();
		type = ColliderType::CIRCLE;

		// Default Radius Value. True value is set outside this method.
		radius = 1.0f;
	}

	void CircleCollider::update()
	{

	}

	void CircleCollider::draw(SDL_Renderer* renderer)
	{
		if (AzurDebug::debug_mode)
		{
			// Not need to show playfield collision. That would be red all the time and would make this whole code useless
			if (entity->tag == ECS_Tag::PLAYFIELD)
			{
				// Playfield is blue to distinguish from other colliders
				SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); // blue
			}
			else if (collider_tags.size() == 1 && collider_tags[0] == ECS_Tag::PLAYFIELD)
			{
				SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // green
			}
			else if (isColliding)
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
			const int32_t diameter = int32_t(radius * 2.0f);

			int32_t x = int32_t(radius - 1);
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
