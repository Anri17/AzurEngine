#include "StageComponent.h"

void StageComponent::init()
{
}

void StageComponent::update()
{
	++frame;

	if (frame == 240) // 4 seconds
	{
		// spawn enemy 1
	}

	if (frame == 600) // 10 seconds
	{
		// spawn enemy 2
	}
}
