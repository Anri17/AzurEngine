#ifndef _ECS_SYSTEM_H
#define _ECS_SYSTEM_H

#include <SDL.h>

#include "Component.h"

namespace ECS
{
	// This class exists so that I can define a generic of systems
	class ISystem
	{
	public:
		virtual void Init() {};
		virtual void Update() {};
		virtual void Render(SDL_Renderer* renderer) {};
	};

	template <typename T>
	class System : public ISystem
	{
	public:
		inline static T* Instance;
	protected:
		ComponentBitSet systemBitset;
	};
}

#endif // _ECS_SYSTEM_H