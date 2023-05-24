#include "BulletComponent.h"

#include "PlayFieldComponent.h"
#include "ECSManager.h"

void BulletComponent::init()
{
	position = entity->GetComponent<PositionComponent>();
}

void BulletComponent::update()
{
	position->y -= speed;

	if (position->y - height / 2 < PlayFieldComponent::Top)
	{
		EntityManager::FlagForDeletion(this->entity);
	}
}
