#include "Soli-Rom.h"
#include "Engine/EntryPoint.h"

#include "layers/GameLayer.h"
//#include "InterfaceLayer.h"

class WeedGame : public SoliRom::App
{
public:
	WeedGame() : SoliRom::App()
	{
		AddLayer(new GameLayer);
		//AddLayer(new InterFaceLayer);
	}

private:
};

SoliRom::App* SoliRom::CreateApp()
{
	return new WeedGame;
}
