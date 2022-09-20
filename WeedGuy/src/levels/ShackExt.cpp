#include "ShackExt.h"

ShackExt* ShackExt::instance = NULL;

ShackExt* ShackExt::Get()
{
	if (!instance)
	{
		instance = new ShackExt;
	}

	return instance;
}

ShackExt::ShackExt()
{
	levelIdentification = LevelId::ShackExt;
	app = SoliRom::App::Get();
	w_game = app->getCurrentWindow();
	assetManager = SoliRom::AssetManager::Get();

	//exterior
	exterior = assetManager->createTexture("assets/shackExt.jpg");
	arrow = assetManager->createTexture("assets/Arrow.png");

	right.setTexture(arrow);
	left.setTexture(arrow);

	level.setSize(w_game->getWidth(), w_game->getHeight());
	right.setSize(128, 128);
	left.setSize(128, 128);
	door.setSize(187, 482);

	right.setPosition(w_game->getWidth() - right.GetRect()->w, (w_game->getHeight() / 2) - (right.GetRect()->h / 2));
	left.setPosition(0, right.GetRect()->y);
	door.setPosition(405, 310);

	//rest
	level.setTexture(exterior);
}

void ShackExt::Load(LevelId _previousLevel)
{
	if (!loadSuccess)
	{
		loadSuccess = true;
	}
}

void ShackExt::Script()
{
	if (loadSuccess)
	{

	}
}


Level::LevelId ShackExt::LevelTransition()
{
	if (SoliRom::EventHandler::click())
	{
		if (SoliRom::EventHandler::mouseInObj(&door))
		{
			loadSuccess = false;
			return LevelId::ShackInt;
		}
	}

	return LevelId::ShackExt;
}

void ShackExt::Draw()
{
	SDL_RenderClear(w_game->getSDL_Renderer());

	level.draw();
	right.draw();
	left.draw(SDL_FLIP_HORIZONTAL);
	door.drawRect(true);


	SDL_RenderPresent(w_game->getSDL_Renderer());
}