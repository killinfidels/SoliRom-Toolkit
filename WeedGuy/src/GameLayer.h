#pragma once
#include "Soli-Rom.h"
#include "Shack.h"

class GameLayer : public SoliRom::Layer
{
public:
	GameLayer();
	~GameLayer() = default;

	virtual void onUpdate() override;

private:
	Shack* shackScene;

	bool exit;
	bool debugBox;

	Timer frameT;

	SoliRom::Window* w_game;
};