#pragma once
#include "Core.h"
#include "../player/Player.h"

class GameLayer : public Layer
{
public:
	GameLayer();
	~GameLayer() = default;

	virtual void OnEvent() override;
	virtual void OnUpdate() override;

	App* game;
	AssetManager* assetM;
	Window* w_game;

	Player* player;

	GameObject map;
	Asset::Texture* t_map;
	SDL_FRect mapRect;

	Timer fps;
};

