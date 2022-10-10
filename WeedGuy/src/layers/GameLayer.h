#pragma once
#include "../core.h"
#include "../objects/items.h"
#include "../levels/Menu.h"
#include "../levels/ShackExt.h"
#include "../levels/ShackInt.h"
#include "../levels/CaveExt.h"
#include "../levels/CaveInt.h"

class GameLayer : public SoliRom::Layer
{
public:
	GameLayer();
	~GameLayer() = default;

	virtual void OnEvent() override;
	virtual void OnUpdate() override;

	void LevelTransitionLogic();

private:
	Level* currentLevel;
	Level::LevelId lastLevel, nextLevel, beforeMenu;

	SoliRom::App* app;

	int prevX = 0, prevY = 0;

	bool exit;
	bool debugBox;
	bool menu = false;

	SoliRom::Timer frameT;

	SoliRom::Window* w_game;

	std::vector<Tree*> trees;
	std::vector<Level::LevelId> treePlace;

	Object loadingScreen;
	SoliRom::Asset::Texture* t_loading;
};