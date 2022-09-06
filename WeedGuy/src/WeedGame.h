#pragma once
#include "Soli-Rom.h"
#include "Engine/EntryPoint.h"

#include "GameLayer.h"
//#include "InterfaceLayer.h"

class WeedGame : public SoliRom::App
{
public:
	WeedGame();

private:
};

WeedGame::WeedGame() : SoliRom::App()
{
	addLayer(new GameLayer);
	//addLayer(new InterFaceLayer);
}

SoliRom::App* SoliRom::App::CreateApp()
{
	return new WeedGame;
}
