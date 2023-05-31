#include "SpriteManager.h"

#include <string>
#include <SDL.h>
#include <SDL_image.h>

#include "AzurLib.h"
#include "AzurDebug.h"

#include "Application.h"

SpriteData* SpriteManager::bullet_a = nullptr;
SpriteData* SpriteManager::player = nullptr;
SpriteData* SpriteManager::blank_texture = nullptr;

void SpriteManager::InitializeSprites()
{
	// Initialize all of the sprites that are going to be used in the game.
	const char* player_filename = "player.png";
	int player_w = 32;
	int player_h = 48;
	int player_x = (int)(-player_w / 2);
	int player_y = (int)(-player_h / 2);
	player = CreateSprite(Application::renderer, player_filename,  player_x, player_y, player_w, player_h);

	const char* bullet_a_filename = "small_bullet.png";
	int bullet_a_w = 12;
	int bullet_a_h = 12;
	int bullet_a_x = (int)(-bullet_a_w / 2);
	int bullet_a_y = (int)(-bullet_a_h / 2);
	bullet_a = CreateSprite(Application::renderer, bullet_a_filename, bullet_a_x, bullet_a_y, bullet_a_w, bullet_a_h);

	const char* blank_texture_filename = "blank_texture.png";
	int blank_texture_w = 1;
	int blank_texture_h = 1;
	int blank_texture_x = (int)(-bullet_a_w / 2);
	int blank_texture_y = (int)(-bullet_a_h / 2);
	blank_texture = CreateSprite(Application::renderer, blank_texture_filename, blank_texture_x, blank_texture_y, blank_texture_w, blank_texture_h);
}

void SpriteManager::DeleteSprites()
{
	SDL_DestroyTexture(player->texture);
	delete player;
	SDL_DestroyTexture(bullet_a->texture);
	delete bullet_a;
}

SpriteData* SpriteManager::CreateSprite(SDL_Renderer* renderer, const char* imageFileName, int x, int y, int w, int h)
{
	SpriteData* sprite = new SpriteData();
	const char* baseDir = SDL_GetBasePath();
	std::string fileDir = baseDir;
	fileDir += imageFileName;

	SDL_Surface* surface = IMG_Load(fileDir.c_str());
	if (surface == NULL)
	{
		DEBUG_CONSOLE_LOG("IMG_Load failed: " << SDL_GetError());
		return nullptr;
	}
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	if (texture == NULL)
	{
		DEBUG_CONSOLE_LOG("SDL_CreateTextureFromSurface failed: " << SDL_GetError());
		return nullptr;
	}
	SDL_FreeSurface(surface);

	sprite->texture = texture;
	sprite->rect.x = Application::GetWindowTrueX(x);
	sprite->rect.y = Application::GetWindowTrueY(y);
	sprite->rect.w = Application::GetWindowTrueX(w);
	sprite->rect.h = Application::GetWindowTrueY(h);

	return sprite;
}
