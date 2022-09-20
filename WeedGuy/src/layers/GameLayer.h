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

	virtual void onUpdate() override;

	void LevelTransitionLogic();

private:
	Level* currentLevel;
	Level::LevelId lastLevel, nextLevel, beforeMenu;

	bool exit;
	bool debugBox;
	bool menu = false;

	SoliRom::Timer frameT;

	SoliRom::Window* w_game;
};