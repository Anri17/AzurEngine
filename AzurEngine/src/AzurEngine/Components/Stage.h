#ifndef _STAGE_COMPONENT_H
#define _STAGE_COMPONENT_H

#include ".\..\ECS.h"

class Stage : public Component
{
public:
	void Init() override;
	void Update() override;

private:
	size_t frame;
};

#endif // _STAGE_COMPONENT_H