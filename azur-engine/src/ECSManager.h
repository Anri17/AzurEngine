#ifndef _ECS_MANAGER_H
#define _ECS_MANAGER_H

#include "EntityTag.h"
#include "Components.h"

class EntityManager
{
public:
	/* Entity Creation Methods */
	static BulletComponent* CreateBulletEntity(float spawn_x, float spawn_y, EntityTag tag);
	static BulletSpawerComponent* CreateBulletSpawnerEntity(float spawn_x, float spawn_y, EntityTag tag);

public:
	static Entity* AddEntity(Entity* entity);

	static void Render(SDL_Renderer* renderer);
	static void Update();
	static void DeleteAllEntities();

	static void DeleteFlagedEntities();
	static void FlagForDeletion(Entity* entity);
private:
	static std::vector<Entity*> entities;
	static std::vector<Entity*> flagged_for_deletion;
};


#endif // _ECS_MANAGER_H