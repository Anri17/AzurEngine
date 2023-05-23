#ifndef _STAGE_COMPONENT_H
#define _STAGE_COMPONENT_H

#include "ECS.h"

class StageComponent : public Component
{
public:
	void init() override;
	void update() override;

private:
	size_t frame;
};


#endif // _STAGE_COMPONENT_H