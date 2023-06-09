#ifndef _UI_SYSTEM_H
#define _UI_SYSTEM_H

#include <vector>

#include "ECS.h"

#include "Components.h"

class UISystem : public ECS::System<UISystem>
{
public:
	UISystem();

	void Init() override;
	void Update() override;
	void Render(SDL_Renderer* renderer) override;

	static void BuildText(const Position* position, Text* text);
public:
	static std::vector<std::pair<Position*, Text*>> entities;

private:
	static const int FONT_RESOLUTION_RATIO;
};

#endif // _UI_SYSTEM_H