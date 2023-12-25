#include "Player.h"

#include <cmath>

#include <SDL.h>

#include ".\..\Application.h"
#include ".\..\InputHandler.h"

#include ".\..\Systems.h"

#include ".\..\AzurDebug.h"

#include "BulletType.h"
#include "PlayField.h"
#include ".\..\AssetManager.h"

void Player::Init()
{
	position = entity->GetComponent<Position>();
	sprite = entity->GetComponent<Sprite>();
	position->x = spawnX;
	position->y = spawnY;
	fire_frame = 0;
}

void Player::Update()
{
	float xVelocity = 0;
	float yVelocity = 0;
	float speed = 0;
	float normalSpeed = 3.0f;
	float focusSpeed = 1.5f;

	if (AzurDebug::debug_mode)
	{
		lives = 99;
	}

	if (!was_hit)
	{
		if (InputHandler::get_key_down(InputHandler::KEY_LSHIFT))
		{
			speed = focusSpeed;
		}
		else
		{
			speed = normalSpeed;
		}

		if (InputHandler::get_key_down(InputHandler::KEY_UP))
		{
			yVelocity += -speed;
		}
		if (InputHandler::get_key_down(InputHandler::KEY_DOWN))
		{
			yVelocity += speed;
		}
		if (InputHandler::get_key_down(InputHandler::KEY_LEFT))
		{
			xVelocity += -speed;
		}
		if (InputHandler::get_key_down(InputHandler::KEY_RIGHT))
		{
			xVelocity += speed;
		}

		// Diagonal Velocity
		if (yVelocity != 0 && xVelocity != 0)
		{
			xVelocity = (float)cos((M_PI / 4.0)) * xVelocity;
			yVelocity = (float)sin((M_PI / 4.0)) * yVelocity;
		}

		position->y += yVelocity;
		position->x += xVelocity;


		// Limit Player Play Field
		if (position->x < PlayField::Left + player_w / 2.0f) position->x = PlayField::Left + player_w / 2.0f;
		if (position->x + player_w / 2.0f > PlayField::Right) position->x = PlayField::Right - player_w / 2.0f;
		if (position->y < PlayField::Top + player_h / 2.0f) position->y = PlayField::Top + player_h / 2.0f;
		if (position->y + player_h / 2.0f > PlayField::Bottom) position->y = PlayField::Bottom - player_h / 2.0f;


		// Fire Bullet
		if (InputHandler::get_key_down(InputHandler::KEY_Z))
		{
			if ((fire_frame % 8) == 0)
			{
				// float bulletSpeed = 4.0f;
				float bulletSpeed = 32.0f;
				float bulletAngle = 270.0f;
				AssetManager::CreateBulletEntityA(
					"Player Bullet",
					this->position->x,
					this->position->y,
					ECS::Tag::BULLET_PLAYER,
					bulletSpeed,
					bulletAngle,
					BulletType::PLAYER);
			}

			fire_frame++;
		}
		else
		{
			fire_frame = 0;
		}
	}

	size_t collider_count = collider->collider_references.size();
	for (size_t i = 0; i < collider_count; ++i)
	{
		Collider* c = collider->collider_references[i];
		if ((c->entity->tag == ECS::Tag::BULLET_ENEMY || c->entity->tag == ECS::Tag::ENEMY) && (!was_hit && !is_invincible))
		{
			ECS::Manager::FlagForDeletion(collider->collider_references[i]->entity);
			--lives;
			was_hit = true;
			sprite->texture = SpriteSystem::blank_texture->texture;
			sprite->rect = SpriteSystem::blank_texture->rect;
			break;
		}
	}

	// Player is dead and is now going to revive
	if (was_hit && lives >= 0)
	{
		revive_frame_count++;
		if (revive_frame_count % revive_cooldown == 0)
		{
			position->x = spawnX;
			position->y = spawnY;
			sprite->texture = SpriteSystem::player->texture;
			sprite->rect = SpriteSystem::player->rect;
			was_hit = false;
			revive_frame_count = 0;
			ECS::Manager::FlagForDeletionAllTagged(ECS::Tag::BULLET_ENEMY);
			is_invincible = true;
		}
	}

	// Player has revived and is now invincible for a few seconds
	if (is_invincible)
	{
		invincibility_frame_count++;
		// Player flashes while invincible
		if (invincibility_frame_count % 3 == 0)
		{
			sprite->texture = SpriteSystem::blank_texture->texture;
			sprite->rect = SpriteSystem::blank_texture->rect;
		}
		if (invincibility_frame_count % 6 == 0)
		{
			sprite->texture= SpriteSystem::player->texture;
			sprite->rect = SpriteSystem::player->rect;
		}

		// Cool down is over, invincibility is over
		if (invincibility_frame_count % invincibility_cooldown == 0)
		{
			// TODO: 
			is_invincible = false;
			sprite->texture = SpriteSystem::player->texture;
			sprite->rect = SpriteSystem::player->rect;
		}
	}
}
