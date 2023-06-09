#ifndef _SPRITE_SYSTEM_H
#define _SPRITE_SYSTEM_H

#include "ECS.h"

#include "SpriteData.h"

class SpriteSystem : public ECS::System<SpriteSystem>
{
public:
	static SpriteData* bullet_a;
	static SpriteData* player;
	static SpriteData* blank_texture;

public:
	static void DeleteSprites();

	SpriteSystem();

	void Init() override;
	void Update() override;
	void Render(SDL_Renderer* renderer) override;

private:
	static SpriteData* CreateSprite(SDL_Renderer* renderer, const char* imageFileName, int x, int y, int w, int h);
};

#endif // _SPRITE_SYSTEM_H
