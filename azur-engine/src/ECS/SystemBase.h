#ifndef _ECS_SYSTEM_BASE_H
#define _ECS_SYSTEM_BASE_H

#include <SDL.h>

namespace ECS
{
	class SystemBase
	{
	public:
		SystemBase();

		virtual void Init();
		virtual void Update();
		virtual void Render(SDL_Renderer* renderer);

		virtual void DeleteNullComponents();

		virtual ~SystemBase();
	};
}

#endif // _ECS_SYSTEM_BASE_H