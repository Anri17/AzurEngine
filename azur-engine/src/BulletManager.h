#ifndef _BULLET_MANAGER_H
#define _BULLET_MANAGER_H

#include <vector>

#include "ECS.h"

class BulletManager
{
public:
	static void Init();
	static void Update();
	static void Render();

private:
	static std::vector<Bullet*> bullets;
};

#endif // _BULLET_MANAGER_H
