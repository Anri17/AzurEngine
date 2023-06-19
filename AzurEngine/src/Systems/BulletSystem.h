#ifndef _BULLET_MANAGER_H
#define _BULLET_MANAGER_H

#include <vector>

#include ".\..\ECS.h"

#include ".\..\Components.h"

class BulletSystem : public ECS::System<BulletSystem>
{
public:
	BulletSystem();
	
	void Init() override;
	void Update() override;
	void Render(SDL_Renderer* renderer) override;

private:
	static std::vector<Bullet*> bullets;
};

#endif // _BULLET_MANAGER_H
