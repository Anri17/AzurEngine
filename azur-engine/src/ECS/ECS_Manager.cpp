#include "ECS_Manager.h"

#include ".\..\Application.h"
#include ".\..\SpriteManager.h"
#include "Component/Sprite.h"

#include ".\..\TextManager.h"

namespace ECS
{
	std::vector<Entity*> ECS_Manager::entities;
	std::vector<Entity*> ECS_Manager::flagged_for_deletion;

	Entity* ECS_Manager::AddEntity(Entity* entity)
	{
		entities.emplace_back(entity);

		return entity;
	}

	Entity* ECS_Manager::CreateBulletEntityA(std::string name, float spawn_x, float spawn_y, ECS_Tag tag, float speed, float angle, BulletType bulletType)
	{
		// TODO: The bullet Type is given but used, for now.
		// 
		// TODO: There is going to be a list of bullet types. This means that I need to check every type and then get the right eindex of bullet to then spawn it.
		// TODO: Might need to move the bullet creation to the BulletTool class and then use this class to creata an object.
		// Initialise Bullet with ECS
		Entity* entity = new Entity();
		entity->name = name;
		entity->tag = tag;
		Position* position = entity->AddComponent<Position>();
		position->x = spawn_x;
		position->y = spawn_y;
		Bullet* bullet = entity->AddComponent<Bullet>();
		bullet->speed = speed;
		bullet->angle = angle;
		Sprite* sprite = entity->AddComponent<Sprite>();
		sprite->texture = SpriteManager::bullet_a->texture;
		sprite->rect = SpriteManager::bullet_a->rect;
		CircleCollider* circleCollider = entity->AddComponent<CircleCollider>();
		circleCollider->radius = 6;
		bullet->collider = circleCollider;
		ECS_Manager::AddEntity(entity);

		return entity;
	}

	Entity* ECS_Manager::CreateBulletSpawnerEntity(std::string name, float spawn_x, float spawn_y, ECS_Tag tag)
	{
		// Initialise Bullet with ECS
		Entity* entity = new Entity();
		entity->name = name;
		entity->tag = tag;
		Position* position = entity->AddComponent<Position>();
		position->x = spawn_x;
		position->y = spawn_y;
		BulletSpawner* bulletSpawner = entity->AddComponent<BulletSpawner>();
		ECS_Manager::AddEntity(entity);

		return entity;
	}

	Entity* ECS_Manager::CreatePlayerEntity(std::string name, ECS_Tag tag)
	{
		Entity* entity = new Entity();
		entity->name = name;
		entity->tag = tag;
		Position* position = entity->AddComponent<Position>();
		CircleCollider* collider = entity->AddComponent<CircleCollider>();
		collider->radius = 2;
		// TODO: NOTE -> Order of Initializarion is very important. the Position and BoxCollider Components need to be created before the Player COmponent so that hte Player Component can initialize it and get their references. Initializing everything in bulk after is not a solution either because the same order of initialization problem persists.
		Sprite* sprite = entity->AddComponent<Sprite>();
		sprite->texture = SpriteManager::player->texture;
		sprite->rect = SpriteManager::player->rect;
		Player* player = entity->AddComponent<Player>();
		player->collider = collider;
		ECS_Manager::AddEntity(entity);

		return entity;
	}

	Entity* ECS_Manager::CreatePlayFieldEntity(std::string name)
	{
		Entity* entity = new Entity();
		entity->AddComponent<PlayField>();
		entity->tag = ECS_Tag::PLAYFIELD;
		BoxCollider* boxCollider = entity->AddComponent<BoxCollider>();
		boxCollider->offset_top = PlayField::Top;
		boxCollider->offset_right = PlayField::Right;
		boxCollider->offset_bottom = PlayField::Bottom;
		boxCollider->offset_left = PlayField::Left;

		ECS_Manager::AddEntity(entity);

		return entity;
	}

	Entity* ECS_Manager::CreateText(std::string name, std::string message, std::string fontpath, int fontsize, SDL_Color color)
	{
		Entity* entity = new Entity();
		entity->tag = ECS_Tag::UI_TEXT;
		Position* position = entity->AddComponent<Position>();
		Text* text = entity->AddComponent<Text>();
		text->SetColor(color);
		text->SetFont(fontpath, fontsize);
		text->SetMessage(message);
		text->SetAlignment(TextAlignment::LEFT);

		TextManager::BuildText(position, text);
		TextManager::entities.push_back(std::pair<Position*, Text*>(position, text));
		ECS_Manager::AddEntity(entity);

		return entity;

	}

	void ECS_Manager::Render(SDL_Renderer* renderer)
	{
		for (int i = 0; i < entities.size(); i++)
		{
			if (entities[i]->active) entities[i]->Draw(renderer);
		}
	}

	void ECS_Manager::Update()
	{
		for (int i = 0; i < entities.size(); i++)
		{
			if (entities[i]->active) entities[i]->Update();
		}
	}

	void ECS_Manager::DeleteAllEntities()
	{
		for (Entity* e : entities)
		{
			delete e;
		}
		entities.clear();
	}

	void ECS_Manager::DeleteFlagedEntities()
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

	void ECS_Manager::FlagForDeletion(Entity* entity)
	{
		flagged_for_deletion.push_back(entity);
	}

	void ECS_Manager::FlagForDeletionAllTagged(ECS_Tag tag)
	{
		for (size_t i = 0; i < entities.size(); ++i)
		{
			if (entities[i]->tag == tag)
			{
				flagged_for_deletion.push_back(entities[i]);
			}
		}
	}
}