#include "BulletSpawnerComponent.h"

#include "ECSManager.h"

void BulletSpawerComponent::init()
{
	position = entity->GetComponent<PositionComponent>();
	frame = 0;
}

void BulletSpawerComponent::update()
{
	frame++;

	if (frame % 60 == 0)
	{
		EntityManager::CreateBulletEntity("Enemy Bullet", this->position->x, this->position->y, ColliderTag::BULLET_ENEMY);
	}
}

BulletSpawerComponent::~BulletSpawerComponent()
{

}