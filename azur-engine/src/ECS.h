#ifndef _ECS_H
#define _ECS_H

#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

#include <SDL.h>

#include "AzurMemoryLeakFinder.h"


enum class EntityTag
{
	UNDEFINED,
	PLAYER,
	ENEMY_BULLET
};

class Component;
class Entity;

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

/*
	An entity is an object that hold many components. These components can be simple ones like position and sprites, and also complex ones for specific tasks.
*/
class Entity
{
public:
	void Update()
	{
		for (size_t i = 0; i < components.size(); ++i)
		{
			Component* c = components[i];
			c->update();
		}
	}

	void Draw(SDL_Renderer* renderer)
	{
		for (size_t i = 0; i < components.size(); ++i)
		{
			Component* c = components[i];
			c->draw(renderer);
		}
	}

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

	~Entity()
	{
		for (size_t i = 0; i < components.size(); ++i)
		{
			Component* c = components[i];
			delete c;
		}
	}

public:
	bool active = true;
	std::vector<Component*> components;

	std::string name = "undefined";
	EntityTag tag = EntityTag::UNDEFINED;

	ComponentArray componentArray;
	ComponentBitSet componentBitSet;
};

#endif // _ECS_H
