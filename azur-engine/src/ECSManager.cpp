#include "ECSManager.h"

Entity* EntityManager::AddEntity(Entity* entity)
{
	entities.emplace_back(entity);

	return entity;
}

Bullet* EntityManager::SpawnBullet(SDL_Renderer* renderer, PlayerComponent* player)
{
	// Initialise Bullet with ECS
	Bullet* bullet = new Bullet(renderer, player->position->x, player->position->y);
	// Save the ESC components
	entities.push_back(bullet);

	return bullet;
}

void EntityManager::DeleteBullet(Bullet* bullet)
{
	std::vector<Entity*>::iterator pos = std::find(entities.begin(), entities.end(), (Entity*)bullet);
	if (pos != entities.end())
	{
		entities.erase(pos);
	}
}

void EntityManager::Render(SDL_Renderer* renderer)
{
	for (int i = 0; i < entities.size(); i++)
	{
		entities[i]->draw(renderer);
	}
}

void EntityManager::Update()
{
	for (int i = 0; i < entities.size(); i++)
	{
		entities[i]->update();
	}
}

void EntityManager::DeleteAllEntities()
{
	for (Entity* e : entities)
	{
		delete e;
	}
	entities.clear();
}

std::vector<Entity*> EntityManager::entities;