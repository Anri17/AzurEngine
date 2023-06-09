#ifndef _ECS_MANAGER_H
#define _ECS_MANAGER_H

#include "Entity.h"
#include "Component.h"
#include "Tag.h"

// TODO: Take the entity Creation Methods outside of the ECS Folder
class CollisionSystem;


namespace ECS
{
	// TODO: Hold a reference to the relevant systems. This should not be in the ECS namespace and Folder anyway...
	class Manager
	{
	public:
		static Entity* AddEntity(Entity* entity);

		static void Render(SDL_Renderer* renderer);
		static void Update();
		static void DeleteAllEntities();

		static void FlagForDeletion(Entity* entity);
		static void FlagForDeletionAllTagged(Tag tag);

		static std::vector<Entity*>* GetEntitiesVector() { return &entities;  }
	private:
		static void DeleteFlaggedEntities();

		static std::vector<Entity*> entities;
		static std::vector<Entity*> flagged_for_deletion;
	};
}

#endif // _ECS_MANAGER_H
