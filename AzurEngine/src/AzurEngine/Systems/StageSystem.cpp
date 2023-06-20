#include "StageSystem.h"

#include "./../Application.h"
#include "./../AssetManager.h"

StageSystem::StageSystem() : 
	world_text(nullptr),
	frame(0),
	messages({})
{
	AzurEngine::Application::systems.push_back(this);
}

void StageSystem::Init()
{
	std::string basepath = SDL_GetBasePath();
	std::string fontname = "SpaceMono-Regular.ttf";
	std::string fontpath = basepath + fontname;
	int fontsize = 16;
	SDL_Color message_color = { 255, 255, 255 };
	world_text = AssetManager::CreateText("World Text", "", fontpath, fontsize, message_color)->GetComponent<Text>();
	world_text->position->x = AzurEngine::Application::base_window_width / 2.0f;
	world_text->position->y = AzurEngine::Application::base_window_height / 2.0f - 20;
	world_text->SetAlignment(TextAlignment::CENTER);

	// The messages vector holds the messages that are going to be displayed in the game world.
	// The pair has the frame at which the correspondig paired message is going to be displayed.
	typedef std::pair<int, std::string> pair;
	messages.push_back(pair(0, "This is a World Text. Text is going to be displayed here"));
	messages.push_back(pair(240, "This is the second message..."));
	messages.push_back(pair(480, "This is the third message..."));
	messages.push_back(pair(720, ""));
	messages.push_back(pair(1048, "By the way, I think Ryuuko was around here somewhere..."));
	messages.push_back(pair(1248, "I ought to ask her what the fuck she is doing in this demo."));
	messages.push_back(pair(1448, "Also, why is she wearing blue clothes. They look horrible."));
	// TODO: Save the data such that the given data is in miliseconds and not in frames...
}

void StageSystem::Update()
{
	for (auto m : messages)
	{
		if (m.first == frame)
			world_text->SetMessage(m.second);
	}

	frame++;
}
