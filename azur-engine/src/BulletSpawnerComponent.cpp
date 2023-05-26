#include "BulletSpawnerComponent.h"

#include "ECSManager.h"

void BulletSpawerComponent::init()
{
	position = entity->GetComponent<PositionComponent>();
	frame = 0;
	bullet_angle = 0.0f;
}

void BulletSpawerComponent::update()
{
	float bullet_speed = 2.0f;
	float full_pattern_angle_offset_change_rate = 8;
	int frame_change = 12;
	frame++;

	if (frame % frame_change == 0)
	{
		int directions = 12;
		int bullet_angle_change_rate = 360 / (directions);

		for (size_t i = 0; i < directions; ++i)
		{
			EntityManager::CreateBulletEntityA(
				"Enemy Bullet",
				this->position->x,
				this->position->y,
				EntityTag::BULLET_ENEMY,
				bullet_speed,
				bullet_angle + full_pattern_angle_offset,
				BulletType::BULLET_A);

			bullet_angle += bullet_angle_change_rate;
			if (bullet_angle >= 360) bullet_angle -= 360;
		}

		full_pattern_angle_offset += full_pattern_angle_offset_change_rate;
		if (full_pattern_angle_offset >= 360) full_pattern_angle_offset -= 360;
	}
}

BulletSpawerComponent::~BulletSpawerComponent()
{

}
