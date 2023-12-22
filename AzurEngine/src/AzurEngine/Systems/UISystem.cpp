#include "UISystem.h"

#include "./../Application.h"
#include "./../AssetManager.h"
#include "./../AzurDebug.h"

const int UISystem::FONT_RESOLUTION_RATIO = 2;

UISystem::UISystem()
{
	AzurEngine::Application::systems.push_back(this);
	entities = ECS::Manager::GetEntitiesVector();
}

void UISystem::Init()
{
	// Initialise Text For Debuging
	std::string basepath = SDL_GetBasePath();
	std::string fontname = "SpaceMono-Regular.ttf";
	std::string fontpath = basepath + fontname;
	int fontsize = 12;
	SDL_Color message_color = { 255, 255, 255 };
	current_frame_text = AssetManager::CreateText("Current Frame Text", "current_frame_text", fontpath, fontsize, message_color)->GetComponent<Text>();
	current_frame_text->position->y = 0;

	mouse_x_text = AssetManager::CreateText("Mouse X Text", "mouse_x_text", fontpath, fontsize, message_color)->GetComponent<Text>();
	mouse_x_text->position->y = (float)current_frame_text->rect.h;

	mouse_y_text = AssetManager::CreateText("Mouse Y Text", "mouse_y_text", fontpath, fontsize, message_color)->GetComponent<Text>();
	mouse_y_text->position->y = mouse_x_text->rect.h + mouse_x_text->position->y;

	player_x_text = AssetManager::CreateText("Player X Text", "player_x_text", fontpath, fontsize, message_color)->GetComponent<Text>();
	player_x_text->position->y = mouse_y_text->rect.h + mouse_y_text->position->y;

	player_y_text = AssetManager::CreateText("Player Y Text", "p_y_text", fontpath, fontsize, message_color)->GetComponent<Text>();
	player_y_text->position->y = player_x_text->rect.h + player_x_text->position->y;

	player_lives_text = AssetManager::CreateText("Player Lives Text", "player_lives_text", fontpath, fontsize, message_color)->GetComponent<Text>();
	player_lives_text->position->y = player_y_text->rect.h + player_y_text->position->y;

	debug_mode_text = AssetManager::CreateText("Debug Mode Text", "debug_mode_text", fontpath, fontsize, message_color)->GetComponent<Text>();
	debug_mode_text->position->y = player_lives_text->rect.h + player_lives_text->position->y;

}

void UISystem::Update()
{
	for (Entity* e : *entities)
	{
		if (!e->active ||
			!(e->HasComponent<Position>() && e->HasComponent<Text>()))
		{
			continue;
		}

		Position* position = e->GetComponent<Position>();
		Text* text = e->GetComponent<Text>();
		BuildText(position, text);
	}

	// TODO: This could probably all go to a DebugSystem type of class. The AzurDebug could be turned into a system like that.
	current_frame_text->SetMessage(std::string("CurrentFrame: " + std::to_string(AzurEngine::Application::current_frame)));
	mouse_x_text->SetMessage(std::string("MouseX: " + std::to_string(AzurEngine::Application::mouse.xPos)));
	mouse_y_text->SetMessage(std::string("MouseY: " + std::to_string(AzurEngine::Application::mouse.yPos)));
	if (AzurEngine::Application::entity_player->active)
	{
		player_x_text->SetMessage(std::string("PlayerX: " + std::to_string(AzurEngine::Application::component_player->position->x)));
		player_y_text->SetMessage(std::string("PlayerY: " + std::to_string(AzurEngine::Application::component_player->position->y)));
		player_lives_text->SetMessage(std::string("Player Lives: " + std::to_string(AzurEngine::Application::component_player->lives)));
	}
	if (AzurDebug::debug_mode)
	{
		debug_mode_text->SetMessage(std::string("Debug Mode: ON"));
	}
	else
	{
		debug_mode_text->SetMessage(std::string("Debug Mode: OFF"));
	}
}

void UISystem::Render(SDL_Renderer* renderer)
{
	for (Entity* e : *entities)
	{
		if (!e->active ||
			!(e->HasComponent<Position>() && e->HasComponent<Text>()))
		{
			continue;
		}

		Position* position = e->GetComponent<Position>();
		Text* text = e->GetComponent<Text>();

		if (text->texture != nullptr)
			SDL_RenderCopy(renderer, text->texture, NULL, &text->rect);
	}
}

void UISystem::BuildText(const Position* position, Text* text)
{
	SDL_DestroyTexture(text->texture);
	SDL_Surface* surface = TTF_RenderText_Solid(text->font, text->message.c_str(), text->color);
	if (surface == nullptr)
	{
		text->rect.x = AzurEngine::Application::GetWindowTrueX(position->x);
		text->rect.y = AzurEngine::Application::GetWindowTrueY(position->y);
		text->rect.w = AzurEngine::Application::GetWindowTrueX(0);
		text->rect.h = AzurEngine::Application::GetWindowTrueY(0);
		text->texture = nullptr;
	}
	else if (text->alignment == TextAlignment::LEFT)
	{
		text->rect.x = (int)AzurEngine::Application::GetWindowTrueX(position->x);
		text->rect.y = (int)AzurEngine::Application::GetWindowTrueY(position->y);
		text->rect.w = (int)AzurEngine::Application::GetWindowTrueX(surface->w / (float)FONT_RESOLUTION_RATIO);
		text->rect.h = (int)AzurEngine::Application::GetWindowTrueY(surface->h / (float)FONT_RESOLUTION_RATIO);
		text->texture = SDL_CreateTextureFromSurface(AzurEngine::Application::renderer, surface);
	}
	else if (text->alignment == TextAlignment::CENTER)
	{
		int full_w = int(surface->w / (float)FONT_RESOLUTION_RATIO);
		int half_w = int(full_w / 2.0f);

		text->rect.x = AzurEngine::Application::GetWindowTrueX(position->x - half_w);
		text->rect.y = AzurEngine::Application::GetWindowTrueY(position->y);
		text->rect.w = (int)AzurEngine::Application::GetWindowTrueX(float(full_w));
		text->rect.h = AzurEngine::Application::GetWindowTrueY(surface->h / (float)FONT_RESOLUTION_RATIO);
		text->texture = SDL_CreateTextureFromSurface(AzurEngine::Application::renderer, surface);
	}
	else if (text->alignment == TextAlignment::RIGHT)
	{
		int full_w = surface->w / FONT_RESOLUTION_RATIO;

		text->rect.x = AzurEngine::Application::GetWindowTrueX(position->x - full_w);
		text->rect.y = AzurEngine::Application::GetWindowTrueY(position->y);
		text->rect.w = AzurEngine::Application::GetWindowTrueX(0);
		text->rect.h = AzurEngine::Application::GetWindowTrueY(surface->h / (float)FONT_RESOLUTION_RATIO);
		text->texture = SDL_CreateTextureFromSurface(AzurEngine::Application::renderer, surface);
	}

	SDL_FreeSurface(surface);
}
