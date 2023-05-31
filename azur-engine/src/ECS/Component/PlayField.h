#ifndef _PLAY_FIELD_COMPONENT_H
#define _PLAY_FIELD_COMPONENT_H

#include <SDL.h>

#include ".\..\ECS_Component.h"

namespace ECS
{
	class PlayField : public Component
	{
	public:
		void init() override;
		void draw(SDL_Renderer* renderer);

		static float Top;
		static float Right;
		static float Bottom;
		static float Left;
	private:
		SDL_Rect playfield_rect;
	};
}

#endif // _PLAY_FIELD_COMPONENT_H