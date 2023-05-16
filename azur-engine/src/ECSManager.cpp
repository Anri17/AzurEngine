#include "ECSManager.h"

std::vector<Entity*> EntityManager::entities;
std::vector<Entity*> EntityManager::flagged_for_deletion;

Entity* EntityManager::AddEntity(Entity* entity)
{
	entities.emplace_back(entity);

	return entity;
}

BulletComponent* EntityManager::SpawnBullet(SDL_Renderer* renderer, PlayerComponent* player)
{
	// Initialise Bullet with ECS
	Entity* bullet = new Entity();
	PositionComponent* pc = bullet->addComponent<PositionComponent>();
	pc->x = player->position->x;
	pc->y = player->position->y;
	BulletComponent* bc = bullet->addComponent<BulletComponent>();
	SpriteComponent* sc = bullet->addComponent<SpriteComponent>();
	sc->setTexture(pc, renderer, "small_bullet.png", -bc->width / 2, -bc->height / 2, bc->width, bc->height);
	BoxColliderComponent* bcc = bullet->addComponent<BoxColliderComponent>();
	bcc->offset_top = -10;
	bcc->offset_right = 10;
	bcc->offset_bottom = 10;
	bcc->offset_left = -10;
	bcc->collisionTagName = "bullet";
	entities.push_back(bullet);

	return bc;
}

void EntityManager::DeleteBullet(BulletComponent* bullet)
{
	std::vector<Entity*>::iterator pos = std::find(entities.begin(), entities.end(), bullet->entity);
	if (pos != entities.end())
	{
		size_t index = pos - entities.begin();
		Entity* e = entities[index];
		delete e;
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

void EntityManager::DeleteFlagedEntities()
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

void EntityManager::FlagForDeletion(Entity* entity)
{
	flagged_for_deletion.push_back(entity);
}
