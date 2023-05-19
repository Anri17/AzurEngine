#include "ECSManager.h"

#include "Application.h"

std::vector<Entity*> EntityManager::entities;
std::vector<Entity*> EntityManager::flagged_for_deletion;

Entity* EntityManager::AddEntity(Entity* entity)
{
	entities.emplace_back(entity);

	return entity;
}

BulletComponent* EntityManager::CreateBulletEntity(std::string name, float spawn_x, float spawn_y, ColliderTag tag)
{
	// Initialise Bullet with ECS
	Entity* bullet = new Entity();
	bullet->name = name;
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
	bcc->tag = tag;
	entities.push_back(bullet);

	return bc;
}

Entity* EntityManager::CreateBulletSpawnerEntity(std::string name, float spawn_x, float spawn_y, ColliderTag tag)
{
	// Initialise Bullet with ECS
	Entity* entity = new Entity();
	entity->name = name;
	PositionComponent* pc = entity->addComponent<PositionComponent>();
	pc->x = spawn_x;
	pc->y = spawn_y;
	BulletSpawerComponent* bsc = entity->addComponent<BulletSpawerComponent>();
	entities.push_back(entity);

	return entity;
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
