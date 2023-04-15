#include "Player.h"

#include <cmath>

#include "InputHandler.h"


Player::Player(SDL_Renderer* renderer)
{
	position = addComponent<PositionComponent>();
	position->x = spawnX;
	position->y = spawnY;
	addComponent<SpriteComponent>()->setTexture(renderer, "player.png", 0, 0, 32, 48);
}

void Player::Logic()
{
	int player_w = 32; // TODO: Get the sprite w through the SDL_Rect.
	int player_h = 48; // TODO: Get the sprite h through the SDL_Rect.
	float xVelocity = 0;
	float yVelocity = 0;
	float speed = 0;
	float normalSpeed = 3.0f;
	float focusSpeed = 1.5f;

	if (InputHandler::GetKeyDown(InputHandler::KEY_LSHIFT))
	{
		speed = focusSpeed;
	}
	else
	{
		speed = normalSpeed;
	}

	if (InputHandler::GetKeyDown(InputHandler::KEY_UP))
	{
		yVelocity += -speed;
	}
	if (InputHandler::GetKeyDown(InputHandler::KEY_DOWN))
	{
		yVelocity += speed;
	}
	if (InputHandler::GetKeyDown(InputHandler::KEY_LEFT))
	{
		xVelocity += -speed;
	}
	if (InputHandler::GetKeyDown(InputHandler::KEY_RIGHT))
	{
		xVelocity += speed;
	}

	// Diagonal Velocity
	if (yVelocity != 0 && xVelocity != 0)
	{
		xVelocity = cos((M_PI / 4.0)) * xVelocity;
		yVelocity = cos((M_PI / 4.0)) * yVelocity;
	}

	position->y += yVelocity;
	position->x += xVelocity;


	// Limit Player Play Field
	if (position->x < screen_boundaries_left) position->x = screen_boundaries_left;
	if (position->x + player_w > screen_boundaries_right) position->x = screen_boundaries_right - player_w;
	if (position->y < screen_boundaries_top) position->y = screen_boundaries_top;
	if (position->y + player_h > screen_boundaries_bottom) position->y = screen_boundaries_bottom - player_h;
}