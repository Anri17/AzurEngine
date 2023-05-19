#include "BulletSpawnerComponent.h"

#include "ECSManager.h"

void BulletSpawerComponent::init()
{
	position = entity->getComponent<PositionComponent>();
	frame = 0;
}

void BulletSpawerComponent::update()
{
	frame++;

	if (frame % 60 == 0)
	{
		EntityManager::CreateBulletEntity(this->position->x, this->position->y, EntityTag::BULLET_ENEMY);
	}
}

BulletSpawerComponent::~BulletSpawerComponent()
{

}
