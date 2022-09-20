#include "GameLayer.h"

GameLayer::GameLayer() : Layer("WeedGuy Main Layer")
{
	w_game = SoliRom::App::Get()->createWindow("Virtual pet weed guy : )", 1280, 960);

	currentLevel = ShackExt::Get();
	nextLevel = lastLevel = currentLevel->GetId();

	printf("\x1B[?25l");
}

void GameLayer::onUpdate()
{
	frameT.Start();

	if (kbhit()) //temp exit no more now its object outlines
		if (getch() == '\r')
			debugBox = !debugBox;
	
	//tells level what the last level so it can load correctly
	if (!currentLevel->Loaded())
	{
		currentLevel->Load(lastLevel);
		lastLevel = currentLevel->GetId();
	}
	
	currentLevel->Script();

	currentLevel->Draw();

	LevelTransitionLogic();

	SR_TRACE("Frametime: %ims", frameT.elapsed());
	printf("\x1B[F");
}

void GameLayer::LevelTransitionLogic()
{
	nextLevel = currentLevel->LevelTransition();

	if (nextLevel != lastLevel)
	{
		switch (nextLevel)
		{
		case Level::Menu:
			currentLevel = Menu::Get();
			break;
		case Level::ShackExt:
			currentLevel = ShackExt::Get();
			break;
		case Level::ShackInt:
			currentLevel = ShackInt::Get();
			break;
		default:
			break;
		}
	}
}
