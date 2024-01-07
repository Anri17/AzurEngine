#include "Entity.h"

namespace ECS
{
	void Entity::Update()
	{
		for (size_t i = 0; i < components.size(); ++i)
		{
			Component* c = components[i];
			c->Update();
		}
	}

	void Entity::Render(SDL_Renderer* renderer)
	{
		for (size_t i = 0; i < components.size(); ++i)
		{
			Component* c = components[i];
			c->Render(renderer);
		}
	}

	Entity::~Entity()
	{
		for (size_t i = 0; i < components.size(); ++i)
		{
			Component* c = components[i];
			c->entity = nullptr;
			components[i] = nullptr;
		}
	}
}