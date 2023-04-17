#include "Bullet.h"

#include "PlayField.h"

Bullet::Bullet(SDL_Renderer* renderer, float x, float y)
{
	position = addComponent<PositionComponent>();
	position->x = x;
	position->y = y;
	addComponent<SpriteComponent>()->setTexture(renderer, "small_bullet.png", 0, 0, 12, 12);
}

void Bullet::Logic()
{
	float speed = 2.5f;
	position->y -= speed;

	if (position->y < PlayField::screen_boundaries_top)
	{
		delete this;
	}
}
