#include "Engine/EntryPoint.h"
#include "Core.h"
#include "game/layers/PlaneGameLayer.h"

class PlaneGame : public App
{
public:
	PlaneGame() : App()
	{
		AddLayer(new GameLayer);
	}


private:

};

SoliRom::App* SoliRom::CreateApp()
{
	return new PlaneGame;
}