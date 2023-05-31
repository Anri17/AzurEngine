#ifndef _ECS_SYSTEM_H
#define _ECS_SYSTEM_H

#include <vector>
#include <string>
#include <bitset>
#include <array>

#include "ECS_Tag.h"

#include <SDL.h>

#include "ECS_Component.h"

namespace ECS
{
	class Component;

	using ComponentID = std::size_t;

	inline ComponentID GetComponentTypeID()
	{
		static ComponentID lastID = 0;
		return lastID++;
	}

	template <typename T> inline ComponentID GetComponentTypeID() noexcept
	{
		static ComponentID typeID = GetComponentTypeID();
		return typeID;
	}

	constexpr std::size_t maxComponents = 32;

	using ComponentBitSet = std::bitset<maxComponents>;
	using ComponentArray = std::array<Component*, maxComponents>;

	/*
		An entity is an object that hold many components. These components can be simple ones like position and sprites, and also complex ones for specific tasks.
	*/
	class Entity
	{
	public:
		void Update();
		void Draw(SDL_Renderer* renderer);
		~Entity();

		template <typename T> bool HasComponent() const
		{
			return componentBitSet[GetComponentTypeID<T>()];
		}

		template <typename T, typename... TArgs>
		T* AddComponent(TArgs&&... mArgs)
		{
			T* c(new T(std::forward<TArgs>(mArgs)...));
			c->entity = this;
			components.emplace_back(c);
			componentArray[GetComponentTypeID<T>()] = c;
			componentBitSet[GetComponentTypeID<T>()] = true;
			c->init();
			return c;
		}

		template <typename T>
		T* GetComponent() const
		{
			auto ptr(componentArray[GetComponentTypeID<T>()]);

			return static_cast<T*>(ptr);
		}

		

	public:
		bool active = true;
		std::vector<Component*> components;

		std::string name = "undefined";
		ECS_Tag tag = ECS_Tag::UNDEFINED;

		ComponentArray componentArray;
		ComponentBitSet componentBitSet;
	};
}

#endif // _ECS_SYSTEM_H
