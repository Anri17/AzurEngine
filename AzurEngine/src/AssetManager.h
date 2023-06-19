#ifndef _ASSET_MANAGER_H
#define _ASSET_MANAGER_H

#include "ECS.h"

#include "Components.h"
#include "Systems.h"

class AssetManager
{
public:
	/* Entity Creation Methods */
	static Entity* CreateBulletEntityA(std::string name, float spawn_x, float spawn_y, ECS::Tag tag, float speed, float angle, BulletType bulletType);
	static Entity* CreateBulletSpawnerEntity(std::string name, float spawn_x, float spawn_y, ECS::Tag tag);
	static Entity* CreatePlayerEntity(std::string name, ECS::Tag tag);
	static Entity* CreatePlayFieldEntity(std::string name);
	static Entity* CreateText(std::string name, std::string message, std::string fontpath, int fontsize, SDL_Color color);
};

#endif // _ASSET_MANAGER_H