#ifndef _COMPONENT_H
#define _COMPONENT_H

#include <SDL.h>

#include "Entity.h"

namespace ECS
{
	class Entity;

	class Component
	{
	public:
		Component() : entity(nullptr) {};

		virtual void Init() {}
		virtual void Update() {}
		virtual void Render(SDL_Renderer* renderer) {}

		virtual ~Component() {}

		Entity* entity;
	private:
	};
}

#endif // _COMPONENTS_H