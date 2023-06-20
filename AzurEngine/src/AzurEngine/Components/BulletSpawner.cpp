#include "BulletSpawner.h"

#include "./../AssetManager.h"

void BulletSpawner::Init()
{
	position = entity->GetComponent<Position>();
	frame = 0;
	bullet_angle = 0.0f;
}

void BulletSpawner::Update()
{
	float bullet_speed = 1.5f;
	float full_pattern_angle_offset_change_rate = 8;
	int frame_change = 24;
	frame++;

	if (frame % frame_change == 0)
	{
		int directions = 6;
		int bullet_angle_change_rate = 360 / (directions);

		for (size_t i = 0; i < directions; ++i)
		{
			AssetManager::CreateBulletEntityA(
				"Enemy Bullet",
				this->position->x,
				this->position->y,
				ECS::Tag::BULLET_ENEMY,
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

BulletSpawner::~BulletSpawner()
{

}
