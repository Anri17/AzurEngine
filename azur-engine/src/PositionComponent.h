#ifndef _POSITION_COMPONENT_H
#define _POSITION_COMPONENT_H



class PositionComponent : public Component
{
public:
	float x = 0.0f;
	float y = 0.0f;

	void init() override
	{
		x = 0.0f;
		y = 0.0f;
	}
};


#endif // _POSITION_COMPONENT_H