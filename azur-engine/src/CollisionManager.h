#ifndef _COLLISION_MANAGER_H
#define _COLLISION_MANAGER_H

#include <vector>

#include "Components.h"

class CollisionManager
{
public:
	static void Update();
	static void AddCollider(BoxColliderComponent* collider);
	static void RemoveCollider(BoxColliderComponent* collider);

private:
	static std::vector<BoxColliderComponent*> colliders;
};


#endif // _COLLISION_MANAGER_H