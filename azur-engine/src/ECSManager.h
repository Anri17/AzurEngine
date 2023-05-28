#ifndef _ECS_MANAGER_H
#define _ECS_MANAGER_H

#include "Components.h"

#include "AzurMemoryLeakFinder.h"

#include "BulletType.h"

class EntityManager
{
public:
	/* Entity Creation Methods */
	static BulletComponent* CreateBulletEntityA(std::string name, float spawn_x, float spawn_y, EntityTag tag, float speed, float angle, BulletType bulletType);
	static Entity* CreateBulletSpawnerEntity(std::string name, float spawn_x, float spawn_y, EntityTag tag);
	static Entity* CreatePlayerEntity(std::string name, EntityTag tag);
	static Entity* CreatePlayFieldEntity(std::string name);
	static Entity* CreateText(std::string name, std::string message, std::string fontpath, int fontsize, SDL_Color color);

public:
	static Entity* AddEntity(Entity* entity);

	static void Render(SDL_Renderer* renderer);
	static void Update();
	static void DeleteAllEntities();

	static void DeleteFlagedEntities();
	static void FlagForDeletion(Entity* entity);
	static void FlagForDeletionAllTagged(EntityTag tag);
private:
	static std::vector<Entity*> entities;
	static std::vector<Entity*> flagged_for_deletion;
};


#endif // _ECS_MANAGER_H