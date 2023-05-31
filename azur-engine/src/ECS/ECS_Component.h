#ifndef _ECS_COMPONENTS_H
#define _ECS_COMPONENTS_H

#include <SDL.h>

#include "ECS_Entity.h"

namespace ECS
{
	class Entity;

	class Component
	{
	public:
		Entity* entity;

		virtual void init() {}
		virtual void update() {}
		virtual void draw(SDL_Renderer* renderer) {}

		virtual ~Component() {}
	private:
	};
}

#endif // _ECS_COMPONENTS_H