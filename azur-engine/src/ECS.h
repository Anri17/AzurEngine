#ifndef _ECS_H
#define _ECS_H

#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

#include <SDL.h>

class Component;
class Entity;

using ComponentID = std::size_t;

inline ComponentID getComponentTypeID()
{
	static ComponentID lastID = 0;
	return lastID++;
}

template <typename T> inline ComponentID getComponentTypeID() noexcept
{
	static ComponentID typeID = getComponentTypeID();
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
	void update()
	{
		for (auto& c : components)
		{
			c->update();
		}
	}

	void draw(SDL_Renderer* renderer)
	{
		for (auto& c : components)
		{
			c->draw(renderer);
		}
	}

	template <typename T> bool hasComponent() const
	{
		return componentBitSet[getComponentTypeID<T>()];
	}

	template <typename T, typename... TArgs>
	T* addComponent(TArgs&&... mArgs)
	{
		T* c(new T(std::forward<TArgs>(mArgs)...));
		c->entity = this;
		std::unique_ptr<Component> uPtr{ c };
		components.emplace_back(std::move(uPtr));

		componentArray[getComponentTypeID<T>()] = c;
		componentBitSet[getComponentTypeID<T>()] = true;

		c->init();

		return c;
	}

	template <typename T>
	T* getComponent() const
	{
		auto ptr(componentArray[getComponentTypeID<T>()]);

		return static_cast<T*>(ptr);
	}

public:
	bool active = true;
	std::vector<std::unique_ptr<Component>> components;

	ComponentArray componentArray;
	ComponentBitSet componentBitSet;
};

#endif // _ECS_H
