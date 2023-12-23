#ifndef _BOX_COLLIDER_H
#define _BOX_COLLIDER_H

#include "Collider.h"
#include "./../AzurLib.h"

class BoxCollider : public Collider {
public:
	void Init() override;

	inline float get_true_top(Position* position)    const { return position->y + offset_top; }
	inline float get_true_right(Position* position)  const { return position->x + offset_right; }
	inline float get_true_bottom(Position* position) const { return position->y + offset_bottom; }
	inline float get_true_left(Position* position)   const { return position->x + offset_left; }
public:
	float offset_top;
	float offset_right;
	float offset_bottom;
	float offset_left;
};

#endif // _BOX_COLLIDER_H