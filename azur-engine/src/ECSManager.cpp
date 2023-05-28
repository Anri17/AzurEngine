#include "ECSManager.h"

#include "Application.h"
#include "SpriteManager.h"

std::vector<Entity*> EntityManager::entities;
std::vector<Entity*> EntityManager::flagged_for_deletion;

Entity* EntityManager::AddEntity(Entity* entity)
{
	entities.emplace_back(entity);

	return entity;
}

BulletComponent* EntityManager::CreateBulletEntityA(std::string name, float spawn_x, float spawn_y, EntityTag tag, float speed, float angle, BulletType bulletType)
{
	// TODO: The bullet Type is given but used, for now.
	// 
	// TODO: There is going to be a list of bullet types. This means that I need to check every type and then get the right eindex of bullet to then spawn it.
	// TODO: Might need to move the bullet creation to the BulletTool class and then use this class to creata an object.
	// Initialise Bullet with ECS
	Entity* entity = new Entity();
	entity->name = name;
	entity->tag = tag;
	PositionComponent* pc = entity->AddComponent<PositionComponent>();
	pc->x = spawn_x;
	pc->y = spawn_y;
	BulletComponent* bc = entity->AddComponent<BulletComponent>();
	bc->speed = speed;
	bc->angle = angle;
	SpriteComponent* sc = entity->AddComponent<SpriteComponent>();
	sc->sprite = SpriteManager::bullet_a;
	CircleColliderComponent* ccc = entity->AddComponent<CircleColliderComponent>();
	ccc->radius = 6;
	EntityManager::AddEntity(entity);

	return bc;
}

Entity* EntityManager::CreateBulletSpawnerEntity(std::string name, float spawn_x, float spawn_y, EntityTag tag)
{
	// Initialise Bullet with ECS
	Entity* entity = new Entity();
	entity->name = name;
	entity->tag = tag;
	PositionComponent* pc = entity->AddComponent<PositionComponent>();
	pc->x = spawn_x;
	pc->y = spawn_y;
	BulletSpawerComponent* bsc = entity->AddComponent<BulletSpawerComponent>();
	EntityManager::AddEntity(entity);

	return entity;
}

Entity* EntityManager::CreatePlayerEntity(std::string name, EntityTag tag)
{
	Entity* entity = new Entity();
	entity->name = name;
	entity->tag = tag;
	PositionComponent* positionComponent = entity->AddComponent<PositionComponent>();
	CircleColliderComponent* playerColliderComponent = entity->AddComponent<CircleColliderComponent>();
	playerColliderComponent->radius = 2;
	// TODO: NOTE -> Order of Initializarion is very important. the Position and BoxCollider Components need to be created before the Player COmponent so that hte Player Component can initialize it and get their references. Initializing everything in bulk after is not a solution either because the same order of initialization problem persists.
	SpriteComponent* sc = entity->AddComponent<SpriteComponent>();
	sc->sprite = SpriteManager::player;
	PlayerComponent* playerComponent = entity->AddComponent<PlayerComponent>();
	playerComponent->collider = playerColliderComponent;
	EntityManager::AddEntity(entity);

	return entity;
}

Entity* EntityManager::CreatePlayFieldEntity(std::string name)
{
	Entity* entity = new Entity();
	entity->AddComponent<PlayFieldComponent>();
	entity->tag = EntityTag::PLAYFIELD;
	BoxColliderComponent* bcc = entity->AddComponent<BoxColliderComponent>();
	bcc->offset_top = PlayFieldComponent::Top;
	bcc->offset_right = PlayFieldComponent::Right;
	bcc->offset_bottom = PlayFieldComponent::Bottom;
	bcc->offset_left = PlayFieldComponent::Left;
	
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

void EntityManager::FlagForDeletionAllTagged(EntityTag tag)
{
	for (size_t i = 0; i < entities.size(); ++i)
	{
		if (entities[i]->tag == tag)
		{
			flagged_for_deletion.push_back(entities[i]);
		}
	}
}
