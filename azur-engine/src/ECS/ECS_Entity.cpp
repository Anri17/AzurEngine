#include "ECS_Entity.h"

namespace ECS
{
	void Entity::Update()
	{
		for (size_t i = 0; i < components.size(); ++i)
		{
			Component* c = components[i];
			c->update();
		}
	}

	void Entity::Draw(SDL_Renderer* renderer)
	{
		for (size_t i = 0; i < components.size(); ++i)
		{
			Component* c = components[i];
			c->draw(renderer);
		}
	}
	Entity::~Entity()
	{
		for (size_t i = 0; i < components.size(); ++i)
		{
			Component* c = components[i];
			c->entity = nullptr;
			//delete c;
			components[i] = nullptr;
		}
	}
}