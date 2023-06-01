#include "BoxCollider.h"

#include ".\..\..\AzurLib.h"

#include ".\..\ECS_Tag.h"
#include ".\..\..\CollisionManager.h"

#include ".\..\..\Application.h"

#include ".\..\..\AzurDebug.h"

namespace ECS
{
	void BoxCollider::draw(SDL_Renderer* renderer)
	{
		// drawing points
		vector2int p0{ Application::GetWindowTrueX(get_true_left()), Application::GetWindowTrueY(get_true_top()) };
		vector2int p1{ Application::GetWindowTrueX(get_true_right()), Application::GetWindowTrueY(get_true_top()) };
		vector2int p2{ Application::GetWindowTrueX(get_true_left ()), Application::GetWindowTrueY(get_true_bottom()) };
		vector2int p3{ Application::GetWindowTrueX(get_true_right()), Application::GetWindowTrueY(get_true_bottom()) };

		if (AzurDebug::debug_mode)
		{
			// This is a debug drawing of the collision box.
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

			SDL_RenderDrawLine(renderer, p0.x, p0.y, p1.x, p1.y);
			SDL_RenderDrawLine(renderer, p1.x, p1.y, p3.x, p3.y);
			SDL_RenderDrawLine(renderer, p2.x, p2.y, p0.x, p0.y);
			SDL_RenderDrawLine(renderer, p3.x, p3.y, p2.x, p2.y);
		}
	}

	void BoxCollider::update()
	{

	}

	void BoxCollider::init()
	{
		Collider::init();
		type = ColliderType::BOX;

		// Test values. Default should be 0. The actual values are set outside of this function.
		offset_top = 0;
		offset_right = 0;
		offset_bottom = 0;
		offset_left = 0;
	}

}
