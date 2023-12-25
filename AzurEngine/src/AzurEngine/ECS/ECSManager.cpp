#include "ECSManager.h"

namespace ECS
{
	std::vector<Entity*> ECSManager::entities;
	std::vector<Entity*> ECSManager::flagged_for_deletion;

	Entity* ECSManager::entity_add(Entity* entity)
	{
		entities.emplace_back(entity);

		return entity;
	}

	// TODO: The Rendering should be extracted to the systems of the game
	void ECSManager::render(SDL_Renderer* renderer)
	{
		for (int i = 0; i < entities.size(); i++)
		{
			if (entities[i]->active) entities[i]->Render(renderer);
		}
	}

	// TODO: The Updating should be extracted to the systems of the game
	void ECSManager::update()
	{
		for (int i = 0; i < entities.size(); i++)
		{
			if (entities[i]->active) entities[i]->Update();
		}
		entity_delete_flagged();
	}

	void ECSManager::entity_delete_all()
	{
		for (Entity* e : entities)
		{
			delete e;
		}
		entities.clear();
	}

	void ECSManager::entity_flag_for_deletion(Entity* entity)
	{
		flagged_for_deletion.push_back(entity);
	}



	void ECSManager::entities_flag_for_deletion_by_tag(Tag tag)
	{
		for (size_t i = 0; i < entities.size(); ++i)
		{
			if (entities[i]->tag == tag)
			{
				flagged_for_deletion.push_back(entities[i]);
			}
		}
	}

	void ECSManager::entity_delete_flagged()
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