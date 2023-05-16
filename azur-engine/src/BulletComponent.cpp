#include "BulletComponent.h"

#include "PlayFieldComponent.h"
#include "ECSManager.h"

void BulletComponent::init()
{
	position = entity->getComponent<PositionComponent>();
}

void BulletComponent::update()
{
	float speed = 2.5f;
	position->y -= speed;

	if (position->y - height / 2 < PlayFieldComponent::Top)
	{
		EntityManager::FlagForDeletion(this->entity);
	}
}
