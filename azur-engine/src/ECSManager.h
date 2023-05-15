#ifndef _ECS_MANAGER_H
#define _ECS_MANAGER_H

#include "Components.h"

class EntityManager
{
public:
	static Entity* AddEntity(Entity* entity);
	static BulletComponent* SpawnBullet(SDL_Renderer* renderer, PlayerComponent* player);
	static void DeleteBullet(BulletComponent* bullet);

	static void Render(SDL_Renderer* renderer);
	static void Update();
	static void DeleteAllEntities();

private:
	static std::vector<Entity*> entities;
};


#endif // _ECS_MANAGER_H