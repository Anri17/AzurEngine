#include "ECSManager.h"

#include "Application.h"

std::vector<Entity*> EntityManager::entities;
std::vector<Entity*> EntityManager::flagged_for_deletion;

Entity* EntityManager::AddEntity(Entity* entity)
{
	entities.emplace_back(entity);

	return entity;
}

BulletComponent* EntityManager::CreateBulletEntity(float spawn_x, float spawn_y, EntityTag tag)
{
	// Initialise Bullet with ECS
	Entity* bullet = new Entity();
	PositionComponent* pc = bullet->addComponent<PositionComponent>();
	pc->x = spawn_x;
	pc->y = spawn_y;
	BulletComponent* bc = bullet->addComponent<BulletComponent>();
	SpriteComponent* sc = bullet->addComponent<SpriteComponent>();
	sc->setTexture(pc, Application::renderer, "small_bullet.png", -bc->width / 2, -bc->height / 2, bc->width, bc->height);
	BoxColliderComponent* bcc = bullet->addComponent<BoxColliderComponent>();
	bcc->offset_top = -10;
	bcc->offset_right = 10;
	bcc->offset_bottom = 10;
	bcc->offset_left = -10;
	bcc->collisionTagName = tag;
	entities.push_back(bullet);

	return bc;
}

BulletSpawerComponent* EntityManager::CreateBulletSpawnerEntity(float spawn_x, float spawn_y, EntityTag tag)
{
	// Initialise Bullet with ECS
	Entity* bulletSpawner = new Entity();
	PositionComponent* pc = bulletSpawner->addComponent<PositionComponent>();
	pc->x = spawn_x;
	pc->y = spawn_y;
	BulletSpawerComponent* bsc = bulletSpawner->addComponent<BulletSpawerComponent>();
	entities.push_back(bulletSpawner);

	return bsc;
}

void EntityManager::Render(SDL_Renderer* renderer)
{
	for (int i = 0; i < entities.size(); i++)
	{
		if (entities[i]->active) entities[i]->draw(renderer);
	}
}

void EntityManager::Update()
{
	for (int i = 0; i < entities.size(); i++)
	{
		if (entities[i]->active) entities[i]->update();
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
