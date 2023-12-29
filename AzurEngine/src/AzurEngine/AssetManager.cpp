#include "AssetManager.h"

Entity* AssetManager::CreateBulletEntityA(std::string name,
										  float       spawn_x,
										  float       spawn_y,
										  ECS::Tag    tag,
										  float       speed,
										  float       angle,
										  BulletType  bulletType) { // TODO: The bullet Type is given but not used, for now.	
	// TODO: There is going to be a list of bullet types. This means that I need to check every type and then get the right eindex of bullet to then spawn it.
	// TODO: Might need to move the bullet creation to the BulletTool class and then use this class to creata an object.
	// Initialise Bullet with ECS
	Entity         *entity;
	Position       *position;
	Bullet         *bullet;
	Sprite         *sprite;
	CircleCollider *circleCollider;

	entity         = new Entity();
	position       = entity->AddComponent<Position>();
	bullet         = entity->AddComponent<Bullet>();
	sprite         = entity->AddComponent<Sprite>();
	circleCollider = entity->AddComponent<CircleCollider>();


	entity->name           = name;
	entity->tag            = tag;
	position->x            = spawn_x;
	position->y            = spawn_y;
	bullet->speed          = speed;
	bullet->angle_deg      = angle;
	sprite->texture        = SpriteSystem::bullet_a->texture;
	sprite->rect           = SpriteSystem::bullet_a->rect;
	circleCollider->radius = 6;
	bullet->collider       = circleCollider;

	ECS::ECSManager::entity_add(entity);

	return entity;
}

Entity* AssetManager::CreateBulletSpawnerEntity(std::string name,
												float       spawn_x,
												float       spawn_y,
												ECS::Tag    tag) {
	Entity        *entity;
	Position      *position;
	BulletSpawner *bulletSpawner;

	entity        = new Entity();
	position      = entity->AddComponent<Position>();
	bulletSpawner = entity->AddComponent<BulletSpawner>();
	
	entity->name = name;
	entity->tag  = tag;
	position->x  = spawn_x;
	position->y  = spawn_y;
	
	ECS::ECSManager::entity_add(entity);

	return entity;
}

Entity* AssetManager::CreatePlayerEntity(std::string name,
										 ECS::Tag    tag) {
	Entity* entity = new Entity();
	entity->name = name;
	entity->tag = tag;
	Position* position = entity->AddComponent<Position>();
	CircleCollider* collider = entity->AddComponent<CircleCollider>();
	collider->radius = 2;
	// TODO: NOTE -> Order of Initializarion is very important. the Position and BoxCollider Components need to be created before the Player COmponent so that hte Player Component can initialize it and get their references. Initializing everything in bulk after is not a solution either because the same order of initialization problem persists.
	Sprite* sprite = entity->AddComponent<Sprite>();
	sprite->texture = SpriteSystem::player->texture;
	sprite->rect = SpriteSystem::player->rect;
	Player* player = entity->AddComponent<Player>();
	player->collider = collider;

	ECS::ECSManager::entity_add(entity);

	return entity;
}

Entity* AssetManager::CreatePlayFieldEntity(std::string name) {
	Entity* entity = new Entity();
	entity->name = name;
	Position* position = entity->AddComponent<Position>();
	entity->AddComponent<PlayField>();
	entity->tag = ECS::Tag::PLAYFIELD;
	BoxCollider* boxCollider = entity->AddComponent<BoxCollider>();
	boxCollider->offset_top = PlayField::Top;
	boxCollider->offset_right = PlayField::Right;
	boxCollider->offset_bottom = PlayField::Bottom;
	boxCollider->offset_left = PlayField::Left;

	ECS::ECSManager::entity_add(entity);

	return entity;
}

Entity* AssetManager::CreateText(std::string name,
								 std::string message,
								 std::string fontpath,
								 int         fontsize,
								 SDL_Color   color) {
	Entity* entity = new Entity();
	entity->name = name;
	entity->tag = ECS::Tag::UI_TEXT;
	Position* position = entity->AddComponent<Position>();
	Text* text = entity->AddComponent<Text>();
	text->SetColor(color);
	text->SetFont(fontpath, fontsize);
	text->SetMessage(message);
	text->SetAlignment(TextAlignment::LEFT);
	UISystem::BuildText(position, text);

	ECS::ECSManager::entity_add(entity);

	return entity;

}
