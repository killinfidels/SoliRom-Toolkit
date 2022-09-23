#pragma once
#include "../core.h"
#include "../levels/Menu.h"
#include "../levels/ShackExt.h"
#include "../levels/ShackInt.h"

class GameLayer : public SoliRom::Layer
{
public:
	GameLayer();
	~GameLayer() = default;

	virtual void OnUpdate() override;

	void LevelTransitionLogic();

private:
	Level* currentLevel;
	Level::LevelId lastLevel, nextLevel, beforeMenu;

	SoliRom::App* app;

	bool exit;
	bool debugBox;
	bool menu = false;

	SoliRom::Timer frameT;

	SoliRom::Window* w_game;
};