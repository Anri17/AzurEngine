#include "BoxCollider.h"

#include ".\..\..\AzurLib.h"

#include ".\..\ECS_Tag.h"
#include ".\..\..\CollisionManager.h"

#include ".\..\..\Application.h"

#include ".\..\..\AzurDebug.h"

namespace ECS
{
	void BoxCollider::init()
	{
		Collider::init();
		type = ColliderType::BOX;
		offset_top = 0;
		offset_right = 0;
		offset_bottom = 0;
		offset_left = 0;
	}
}
