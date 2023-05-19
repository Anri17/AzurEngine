#ifndef _COLLISION_MANAGER_H
#define _COLLISION_MANAGER_H

#include <vector>

#include "Components.h"

class CollisionManager
{
public:
	static void Update();
	static void AddCollider(ColliderComponent* collider);
	static void RemoveCollider(ColliderComponent* collider);

private:
	static std::vector<ColliderComponent*> colliders;
};


#endif // _COLLISION_MANAGER_H