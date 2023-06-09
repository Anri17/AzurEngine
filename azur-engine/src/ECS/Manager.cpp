#include "Manager.h"

namespace ECS
{
	std::vector<Entity*> Manager::entities;
	std::vector<Entity*> Manager::flagged_for_deletion;

	Entity* Manager::AddEntity(Entity* entity)
	{
		entities.emplace_back(entity);

		return entity;
	}

	// TODO: The Rendering should be extracted to the systems of the game
	void Manager::Render(SDL_Renderer* renderer)
	{
		for (int i = 0; i < entities.size(); i++)
		{
			if (entities[i]->active) entities[i]->Draw(renderer);
		}
	}

	// TODO: The Updating should be extracted to the systems of the game
	void Manager::Update()
	{
		for (int i = 0; i < entities.size(); i++)
		{
			if (entities[i]->active) entities[i]->Update();
		}
		DeleteFlaggedEntities();
	}

	void Manager::DeleteAllEntities()
	{
		for (Entity* e : entities)
		{
			delete e;
		}
		entities.clear();
	}

	void Manager::FlagForDeletion(Entity* entity)
	{
		flagged_for_deletion.push_back(entity);
	}



	void Manager::FlagForDeletionAllTagged(Tag tag)
	{
		for (size_t i = 0; i < entities.size(); ++i)
		{
			if (entities[i]->tag == tag)
			{
				flagged_for_deletion.push_back(entities[i]);
			}
		}
	}

	void Manager::DeleteFlaggedEntities()
	{
		for (size_t i = 0; i < flagged_for_deletion.size(); ++i)
		{
			Entity* entity = flagged_for_deletion[i];

			std::vector<Entity*>::iterator pos = std::find(entities.begin(), entities.end(), entity);
			if (pos != entities.end())
			{
				size_t index = pos - entities.begin();
				Entity* e = entities[index];
				delete e;
				entities.erase(pos);
			}
		}
		flagged_for_deletion.clear();
	}

}