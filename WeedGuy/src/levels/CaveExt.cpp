#include "CaveExt.h"

CaveExt* CaveExt::instance = NULL;

CaveExt* CaveExt::Get()
{
	if (!instance)
	{
		instance = new CaveExt;
	}

	return instance;
}

CaveExt::CaveExt()
{
	levelIdentification = LevelId::CaveExt;

	t_exterior = assetManager->createTexture("assets/CaveExtBLACK.jpg");
	t_arrow = assetManager->createTexture("assets/Arrow.png");
	a_entrance = assetManager->createAnimation("assets/CaveEntrance_1.png");

	right.SetTexture(t_arrow);
	level.SetTexture(t_exterior);

	level.setSize(w_game->getWidth(), w_game->getHeight());
	right.setSize(128, 128);
	caveEntrance.setSize(700, 700);

	right.setPosition(w_game->getWidth() - right.GetRect()->w, (w_game->getHeight() / 2) - (right.GetRect()->h / 2));
	caveEntrance.setPosition(100, 200);

	a_entrance->Start();
}

void CaveExt::Load(LevelId _previousLevel)
{
	if (!loadSuccess)
	{
		loadSuccess = true;
	}
}

void CaveExt::Script()
{
	if (loadSuccess)
	{
		caveEntrance.SetTexture(a_entrance->Get());
	}
}


Level::LevelId CaveExt::LevelTransition()
{
	LevelId tempID = levelIdentification;

	if (SoliRom::EventHandler::click())
	{
		if (SoliRom::EventHandler::mouseInObj(&right))
			tempID = LevelId::ShackExt;

		if (SoliRom::EventHandler::mouseInObj(&caveEntrance))
			tempID = LevelId::CaveInt;
	}

	if (tempID != levelIdentification)
	{
		loadSuccess = false;
		return tempID;
	}

	return LevelId::CaveExt;
}

void CaveExt::Draw()
{
	//level.Draw();
	right.Draw();
	caveEntrance.Draw();
	//caveEntrance.DrawRect(true);
}