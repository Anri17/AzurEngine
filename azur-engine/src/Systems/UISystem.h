#ifndef _UI_SYSTEM_H
#define _UI_SYSTEM_H

#include <vector>

#include ".\..\ECS.h"

#include ".\..\Components.h"

// I am not sure I want to have the UI functions and the Scene elements combined together like this.
// I might have to separate this class further
class UISystem : public ECS::System<UISystem>
{
public:
	UISystem();

	void Init() override;
	void Update() override;
	void Render(SDL_Renderer* renderer) override;

	static void BuildText(const Position* position, Text* text);

private:
	static const int FONT_RESOLUTION_RATIO;

	
	Text* current_frame_text = nullptr;
	Text* mouse_x_text = nullptr;
	Text* mouse_y_text = nullptr;
	Text* player_x_text = nullptr;
	Text* player_y_text = nullptr;
	Text* player_lives_text = nullptr;
	Text* debug_mode_text = nullptr;


	std::vector<Entity*>* entities;
};

#endif // _UI_SYSTEM_H