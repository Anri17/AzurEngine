#ifndef _ECS_MANAGER_H
#define _ECS_MANAGER_H

#include "ECS_Entity.h"
#include "ECS_Component.h"

#include "Component/Position.h"
#include "Component/BoxCollider.h"
#include "Component/Bullet.h"
#include "Component/BulletType.h"
#include "Component/BulletSpawner.h"
#include "Component/CircleCollider.h"
#include "Component/Collider.h"
#include "Component/Player.h"
#include "Component/PlayField.h"
#include "Component/Sprite.h"
#include "Component/Stage.h"
#include "Component/Text.h"


namespace ECS
{
	class ECS_Manager
	{
	public:
		/* Entity Creation Methods */
		static Entity* CreateBulletEntityA(std::string name, float spawn_x, float spawn_y, ECS_Tag tag, float speed, float angle, BulletType bulletType);
		static Entity* CreateBulletSpawnerEntity(std::string name, float spawn_x, float spawn_y, ECS_Tag tag);
		static Entity* CreatePlayerEntity(std::string name, ECS_Tag tag);
		static Entity* CreatePlayFieldEntity(std::string name);
		static Entity* CreateText(std::string name, std::string message, std::string fontpath, int fontsize, SDL_Color color);

	public:
		static Entity* AddEntity(Entity* entity);

		static void Render(SDL_Renderer* renderer);
		static void Update();
		static void DeleteAllEntities();

		static void DeleteFlagedEntities();
		static void FlagForDeletion(Entity* entity);
		static void FlagForDeletionAllTagged(ECS_Tag tag);
	private:
		static std::vector<Entity*> entities;
		static std::vector<Entity*> flagged_for_deletion;
	};
}

#endif // _ECS_MANAGER_H
