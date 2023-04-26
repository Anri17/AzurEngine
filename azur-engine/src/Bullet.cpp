#include "Bullet.h"

#include "PlayField.h"
#include "ECSManager.h"

Bullet::Bullet(SDL_Renderer* renderer, float x, float y)
{
	position = addComponent<PositionComponent>();
	position->x = x;
	position->y = y;
	addComponent<SpriteComponent>()->setTexture(position, renderer, "small_bullet.png", -width / 2, -height / 2, width, height);
}

void Bullet::Logic()
{
	float speed = 2.5f;
	position->y -= speed;

	if (position->y - height / 2 < PlayField::Top)
	{
		EntityManager::DeleteBullet(this);
	}
}
