#include "CircleCollider.h"


#include ".\..\..\Application.h"
#include ".\..\..\AzurLib.h"
#include ".\..\..\AzurDebug.h"
#include ".\..\ECS_Tag.h"
namespace ECS
{
	void CircleCollider::init()
	{
		Collider::init();
		type = ColliderType::CIRCLE;
		radius = 1.0f;
	}
}
