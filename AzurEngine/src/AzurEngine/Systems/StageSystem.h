#ifndef _STAGE_SYSTEM_H
#define _STAGE_SYSTEM_H

#include "./../ECS.h"
#include "./../Components.h"

class StageSystem : public ECS::System<StageSystem>
{
public:
	StageSystem();

	void Init() override;
	void Update() override;
private:
	// Hold the data of the enemies and what not that are going to be spawned in the stage



	Text* world_text;
	std::vector<std::pair<int, std::string>> messages;
	int frame;
};

#endif // _STAGE_SYSTEM_H
