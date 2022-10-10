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

	//exterior
	t_shack = assetManager->createTexture("assets/Shack.png");
	arrow = assetManager->createTexture("assets/Arrow.png");

	right.SetTexture(arrow);
	left.SetTexture(arrow);

	shack.setSize(900, 900);
	right.setSize(128, 128);
	left.setSize(128, 128);
	door.setSize(124, 254);

	shack.setPosition(80, 60);
	right.setPosition(w_game->getWidth() - right.GetRect()->w, (w_game->getHeight() / 2) - (right.GetRect()->h / 2));
	left.setPosition(0, right.GetRect()->y);
	door.setPosition(396, 568);

	//rest
	shack.SetTexture(t_shack);
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
	LevelId tempID = levelIdentification;
	if (SoliRom::EventHandler::click())
	{
		if (SoliRom::EventHandler::mouseInObj(&door))
			tempID = LevelId::ShackInt;

		if (SoliRom::EventHandler::mouseInObj(&left))
			tempID = LevelId::CaveExt;
	}

	if (tempID != levelIdentification)
	{
		loadSuccess = false;
		return tempID;
	}

	return LevelId::ShackExt;
}

void ShackExt::Draw()
{
	shack.Draw();
	right.Draw();
	left.Draw(SDL_FLIP_HORIZONTAL);
	door.DrawRect(true);
}