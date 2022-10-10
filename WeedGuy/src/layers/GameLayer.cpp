#include "GameLayer.h"

GameLayer::GameLayer() : Layer("WeedGuy Main Layer")
{
	app = SoliRom::App::Get();
	w_game = app->CreateWindow("Virtual pet weed guy : )", 1280, 960);
	app->SetCurrentWindow(w_game->getWindowName());

	currentLevel = ShackExt::Get();
	nextLevel = lastLevel = currentLevel->GetId();

	printf("\x1B[?25l");
}

void GameLayer::OnUpdate()
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