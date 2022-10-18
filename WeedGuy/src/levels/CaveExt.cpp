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

	level.SetSize(w_game->getWidth(), w_game->getHeight());
	right.SetSize(128, 128);
	caveEntrance.SetSize(700, 700);

	right.SetPos(w_game->getWidth() - right.GetRect()->w, (w_game->getHeight() / 2) - (right.GetRect()->h / 2));
	caveEntrance.SetPos(100, 200);

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

	if (SoliRom::Input::Click())
	{
		if (SoliRom::Input::MouseInRect(right.GetScreenRect()))
			tempID = LevelId::ShackExt;

		if (SoliRom::Input::MouseInRect(caveEntrance.GetScreenRect()))
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