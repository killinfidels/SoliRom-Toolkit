#include "GameLayer.h"

GameLayer::GameLayer() : Layer("WeedGuy Main Layer")
{
	app = SoliRom::App::Get();
	w_game = app->CreateWindow("Virtual pet weed guy : )", 1280, 960);
	app->SetCurrentWindow(w_game->getWindowName());
	SDL_SetWindowFullscreen(w_game->getSDL_Window(), SDL_WINDOW_FULLSCREEN_DESKTOP);
	SDL_SetWindowResizable(w_game->getSDL_Window(), SDL_FALSE);

	t_loading = SoliRom::AssetManager::Get()->createTexture("Engine/Loading.png");

	loadingScreen.setSize(w_game->getWidth(), w_game->getHeight());
	loadingScreen.SetTexture(t_loading);

	currentLevel = ShackExt::Get();
	nextLevel = lastLevel = currentLevel->GetId();

	printf("\x1B[?25l");
}

void GameLayer::OnEvent()
{
	if (SoliRom::EventHandler::click())
	{
		int tempX = SoliRom::EventHandler::getMouse().x;
		int tempY = SoliRom::EventHandler::getMouse().y;

		SR_TRACE("x: %i y: %i w: %i h: %i", prevX, prevY, tempX - prevX, tempY - prevY);

		prevX = SoliRom::EventHandler::getMouse().x;
		prevY = SoliRom::EventHandler::getMouse().y;

		//debug tree spawner
		if (SoliRom::EventHandler::keyPressed(SDLK_t))
		{
			trees.push_back(new Tree(0, 700, tempX, tempY));
			treePlace.emplace_back(currentLevel->GetId());

			SR_WARN("trees.push_back(new Tree(%i, %i, %i, %i));", 0, trees.back()->GetRect()->w, tempX, tempY);
		}

		if (SoliRom::EventHandler::keyPressed(SDLK_r) && SoliRom::EventHandler::keyPressed(SDLK_t))
		{
			trees.clear();
		}
	}

	if (SoliRom::EventHandler::keyPressed(SDLK_ESCAPE))
	{
		app->Quit();
	}
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

	for (int i = 0; i < trees.size(); i++)
	{
		if (treePlace[i] == currentLevel->GetId())
		{
			trees[i]->Animate();
			trees[i]->Draw();
		}
	}

	currentLevel->Draw();


	LevelTransitionLogic();

	//SR_TRACE("Frametime: %ims", frameT.elapsed());
	//printf("\x1B[F");
}



void GameLayer::LevelTransitionLogic()
{
	nextLevel = currentLevel->LevelTransition();

	if (nextLevel != lastLevel)
	{
		loadingScreen.Draw();
		SDL_RenderPresent(w_game->getSDL_Renderer());

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
		case Level::CaveExt:
			currentLevel = CaveExt::Get();
			break;
		case Level::CaveInt:
			currentLevel = CaveInt::Get();
			break;
		default:
			break;
		}
	}
}
