﻿#include "ECSManager.h"

#include "Application.h"
#include "SpriteManager.h"

std::vector<Entity*> EntityManager::entities;
std::vector<Entity*> EntityManager::flagged_for_deletion;

Entity* EntityManager::AddEntity(Entity* entity)
{
	entities.emplace_back(entity);

	return entity;
}

BulletComponent* EntityManager::CreateBulletEntityA(std::string name, float spawn_x, float spawn_y, ColliderTag tag, float speed)
{
	// TODO: instead of creating a sprite for each component, create an class with preloaded asset textures, and use that to reference the needed texture for each of the bullet that uses it
	// Initialise Bullet with ECS
	Entity* entity = new Entity();
	entity->name = name;
	PositionComponent* pc = entity->AddComponent<PositionComponent>();
	pc->x = spawn_x;
	pc->y = spawn_y;
	BulletComponent* bc = entity->AddComponent<BulletComponent>();
	bc->speed = speed;
	SpriteComponent* sc = entity->AddComponent<SpriteComponent>();
	sc->sprite = SpriteManager::bullet_a;
	// sc->setTexture(Application::renderer, "small_bullet.png", -bc->width / 2, -bc->height / 2, bc->width, bc->height);
	BoxColliderComponent* bcc = entity->AddComponent<BoxColliderComponent>();
	bcc->offset_top = -10;
	bcc->offset_right = 10;
	bcc->offset_bottom = 10;
	bcc->offset_left = -10;
	bcc->tag = tag;
	EntityManager::AddEntity(entity);

	return bc;
}

Entity* EntityManager::CreateBulletSpawnerEntity(std::string name, float spawn_x, float spawn_y, ColliderTag tag)
{
	
	// Initialise Bullet with ECS
	Entity* entity = new Entity();
	entity->name = name;
	PositionComponent* pc = entity->AddComponent<PositionComponent>();
	pc->x = spawn_x;
	pc->y = spawn_y;
	BulletSpawerComponent* bsc = entity->AddComponent<BulletSpawerComponent>();
	EntityManager::AddEntity(entity);

	return entity;
}

Entity* EntityManager::CreatePlayerEntity(std::string name, ColliderTag tag)
{
	Entity* entity = new Entity();
	entity->name = name;
	PositionComponent* positionComponent = entity->AddComponent<PositionComponent>();
	BoxColliderComponent* playerColliderComponent = entity->AddComponent<BoxColliderComponent>();
	playerColliderComponent->offset_top = -20;
	playerColliderComponent->offset_right = 12;
	playerColliderComponent->offset_bottom = 20;
	playerColliderComponent->offset_left = -12;
	playerColliderComponent->tag = tag;
	/*
	CircleColliderComponent* playerColliderComponent = entity->AddComponent<CircleColliderComponent>();
	playerColliderComponent->radius = 12;
	playerColliderComponent->tag = tag;
	*/
	PlayerComponent* playerComponent = entity->AddComponent<PlayerComponent>();	// TODO: NOTE -> Order of Initializarion is very important. the Position and BoxCollider Components need to be created before the Player COmponent so that hte Player Component can initialize it and get their references. Initializing everything in bulk after is not a solution either because the same order of initialization problem persists.
	SpriteComponent* sc = entity->AddComponent<SpriteComponent>();
	sc->sprite = SpriteManager::player;
	// sc->setTexture(Application::renderer, "player.png", -playerComponent->player_w / 2, -playerComponent->player_h / 2, playerComponent->player_w, playerComponent->player_h);
	playerComponent->collider = playerColliderComponent;
	EntityManager::AddEntity(entity);

	return entity;
}

Entity* EntityManager::CreatePlayFieldEntity(std::string name)
{
	Entity* entity = new Entity();
	entity->AddComponent<PlayFieldComponent>();
	EntityManager::AddEntity(entity);

	return entity;
}

void EntityManager::Render(SDL_Renderer* renderer)
{
	for (int i = 0; i < entities.size(); i++)
	{
		if (entities[i]->active) entities[i]->Draw(renderer);
	}
}

void EntityManager::Update()
{
	for (int i = 0; i < entities.size(); i++)
	{
		if (entities[i]->active) entities[i]->Update();
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
