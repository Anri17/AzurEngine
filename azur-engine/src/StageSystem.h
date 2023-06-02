#ifndef _STAGE_SYSTEM_H
#define _STAGE_SYSTEM_H

#include "ECS.h"

class StageSystem
{
public:
	static void Init();
	static void Update();
private:
	// Hold the data of the enemies and what not that are going to be spawned in the stage



	static Text* world_text;
	static std::vector<std::pair<int, std::string>> messages;
	static int frame;
};

#endif // _STAGE_SYSTEM_H
