#ifndef _BOX_COLLIDER_H
#define _BOX_COLLIDER_H

#include ".\..\..\AzurLib.h"

#include "Collider.h"

namespace ECS
{
	class BoxCollider : public Collider
	{
	public:
		void init() override;

		inline float get_true_top()    const { return position->y + offset_top; }
		inline float get_true_right()  const { return position->x + offset_right; }
		inline float get_true_bottom() const { return position->y + offset_bottom; }
		inline float get_true_left()   const { return position->x + offset_left; }
	public:
		float offset_top;
		float offset_right;
		float offset_bottom;
		float offset_left;
	};
}
#endif // _BOX_COLLIDER_H