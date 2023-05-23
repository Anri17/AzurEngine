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
	PositionComponent* pc = bullet->AddComponent<PositionComponent>();
	pc->x = spawn_x;
	pc->y = spawn_y;
	BulletComponent* bc = bullet->AddComponent<BulletComponent>();
	SpriteComponent* sc = bullet->AddComponent<SpriteComponent>();
	sc->setTexture(pc, Application::renderer, "small_bullet.png", -bc->width / 2, -bc->height / 2, bc->width, bc->height);
	BoxColliderComponent* bcc = bullet->AddComponent<BoxColliderComponent>();
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
	PositionComponent* pc = entity->AddComponent<PositionComponent>();
	pc->x = spawn_x;
	pc->y = spawn_y;
	BulletSpawerComponent* bsc = entity->AddComponent<BulletSpawerComponent>();
	entities.push_back(entity);

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
	entity->
		AddComponent<SpriteComponent>()->
		setTexture(positionComponent, Application::renderer, "player.png", -playerComponent->player_w / 2, -playerComponent->player_h / 2, playerComponent->player_w, playerComponent->player_h);
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
