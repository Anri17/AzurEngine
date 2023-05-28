#ifndef _POSITION_COMPONENT_H
#define _POSITION_COMPONENT_H

#include <string>
#include <SDL.h>
#include <SDL_image.h>

#include "ECS.h"

class PositionComponent : public Component
{
public:
	float x = 0.0f;
	float y = 0.0f;

	void init() override;
};


#endif // _POSITION_COMPONENT_H