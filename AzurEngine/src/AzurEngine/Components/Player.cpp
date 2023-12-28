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

void Player::Init() {
	player_w             = 32;
	player_h             = 48;
	lives                = 2;
	spawnX               = 320.0f;
	spawnY               = 400.0f;
	is_dead              = false;
	is_invincible        = false;
	normalSpeed          = 3.0f;
	focusSpeed           = 1.5f;
	death_frame_duration = 90;
	bullet_speed         = 32.0f;
	bullet_angle         = 270.0f;

	position    = entity->GetComponent<Position>();
	sprite      = entity->GetComponent<Sprite>();
	position->x = spawnX;
	position->y = spawnY;
	fire_frame  = 0;
}

void Player::Update() {
	if (AzurDebug::debug_mode) {
		lives = 99;
	}

	if (!is_dead) {
		if (InputHandler::get_key_down(InputHandler::KEY_LSHIFT)) {
			speed = focusSpeed;
		}
		else {
			speed = normalSpeed;
		}

		yVelocity = 0;
		xVelocity = 0;
		if (InputHandler::get_key_down(InputHandler::KEY_UP)) {
			yVelocity += -speed;
		}
		if (InputHandler::get_key_down(InputHandler::KEY_DOWN)) {
			yVelocity +=  speed;
		}
		if (InputHandler::get_key_down(InputHandler::KEY_LEFT)) {
			xVelocity += -speed;
		}
		if (InputHandler::get_key_down(InputHandler::KEY_RIGHT)) {
			xVelocity +=  speed;
		}

		// Diagonal Velocity
		if (yVelocity != 0 &&
			xVelocity != 0) {
			xVelocity = (float)cos((M_PI / 4.0)) * xVelocity;
			yVelocity = (float)sin((M_PI / 4.0)) * yVelocity;
		}

		// Move player
		position->y += yVelocity;
		position->x += xVelocity;

		// Limit Player Play Field
		if (position->x < PlayField::Left + player_w / 2.0f) {
			position->x = PlayField::Left + player_w / 2.0f;
		}
		if (position->x + player_w / 2.0f > PlayField::Right) {
			position->x = PlayField::Right - player_w / 2.0f;
		}
		if (position->y < PlayField::Top + player_h / 2.0f) {
			position->y = PlayField::Top + player_h / 2.0f;
		}
		if (position->y + player_h / 2.0f > PlayField::Bottom) {
			position->y = PlayField::Bottom - player_h / 2.0f;
		}


		// Fire Bullet
		if (InputHandler::get_key_down(InputHandler::KEY_Z)) {
			if ((fire_frame % 8) == 0) {
				AssetManager::CreateBulletEntityA(
				    "Player Bullet",
				    this->position->x,
				    this->position->y,
				    ECS::Tag::BULLET_PLAYER,
				    bullet_speed,
				    bullet_angle,
				    BulletType::PLAYER);
			}
			++fire_frame;
		}
		else {
			fire_frame = 0;
		}
	}

	// Bullet Collision
	collider_count = collider->collider_references.size();
	for (size_t i = 0; i < collider_count; ++i) {
		Collider *c;
		c = collider->collider_references[i];
		if ((c->entity->tag == ECS::Tag::BULLET_ENEMY ||
			 c->entity->tag == ECS::Tag::ENEMY) &&
			(!is_dead &&
			 !is_invincible)){ // collision with enemy bullet -> death
			--lives;
			is_dead           = true;
			death_frame_count = 0;
			sprite->texture   = SpriteSystem::blank_texture->texture;
			sprite->rect      = SpriteSystem::blank_texture->rect;
			ECS::ECSManager::entity_flag_for_deletion(collider->collider_references[i]->entity);
			break;
		}
	}

	// Player is dead and is now going to revive
	if (is_dead && lives >= 0) {
		++death_frame_count;
		if (death_frame_count % death_frame_duration == 0) {
			// set player texture and initial position
			position->x     = spawnX;
			position->y     = spawnY;
			sprite->texture = SpriteSystem::player->texture;
			sprite->rect    = SpriteSystem::player->rect;
			
			// set player state
			is_dead       = false;
			is_invincible = true;
			
			invincibility_frame_count = 0;
			ECS::ECSManager::entities_flag_for_deletion_by_tag(ECS::Tag::BULLET_ENEMY);
		}
	}

	// Player has revived and is now invincible for a few seconds
	if (is_invincible) {
		++invincibility_frame_count;
		// Player flashes while invincible
		if (invincibility_frame_count % 3 == 0) {
			sprite->texture = SpriteSystem::blank_texture->texture;
			sprite->rect    = SpriteSystem::blank_texture->rect;
		}
		if (invincibility_frame_count % 6 == 0) {
			sprite->texture = SpriteSystem::player->texture;
			sprite->rect    = SpriteSystem::player->rect;
		}

		// Cool down is over, invincibility is over
		if (invincibility_frame_count % invincibility_frame_duration == 0) {
			is_invincible   = false;
			sprite->texture = SpriteSystem::player->texture;
			sprite->rect    = SpriteSystem::player->rect;
		}
	}
}
