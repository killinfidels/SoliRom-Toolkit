#include "CaveInt.h"

CaveInt* CaveInt::instance = NULL;

CaveInt* CaveInt::Get()
{
	if (!instance)
	{
		instance = new CaveInt;
	}

	return instance;
}

CaveInt::CaveInt()
{
	levelIdentification = LevelId::CaveInt;

	t_background = assetManager->createTexture("assets/cavebackground.jpg");
	t_arrowDown = assetManager->createTexture("assets/ArrowDown.png");

	back.SetTexture(t_arrowDown);
	level.SetTexture(t_background);

	level.SetSize(w_game->getWidth(), w_game->getHeight());
	back.SetSize(128, 128);

	back.SetPos((w_game->getWidth() / 2) - (back.GetRect()->w / 2), w_game->getHeight() - back.GetRect()->h);

	cam.x = 0;
	cam.y = 0;
	cam.z = 0;

	for (int i = 0; i < 20; i++)
	{
		caveTunnels.emplace_back();
		caveTunnels[i].z = wallSpacing * i + cam.screenDistance;
	}

	CaveWalls::LoadTextureAndCamera("assets/shroom_cave.png", &cam);
}

void CaveInt::Load(LevelId _previousLevel)
{
	if (!loadSuccess)
	{
		cam.z = 0;
		loadSuccess = true;
	}
}

void CaveInt::Script()
{
	if (loadSuccess)
	{
		if (SoliRom::Input::keyPressed(SDLK_w))
		{
			cam.z += 10;
		}

		if (SoliRom::Input::keyPressed(SDLK_s))
		{
			cam.z -= 10;
		}
	}
}

Level::LevelId CaveInt::LevelTransition()
{
	LevelId tempID = levelIdentification;
	if (SoliRom::Input::Click())
	{
		if (SoliRom::Input::MouseInRect(back.GetScreenRect()))
			tempID = LevelId::CaveExt;

	}

	if (cam.z < -20)
	{
		tempID = LevelId::CaveExt;
	}

	if (tempID != levelIdentification)
	{
		loadSuccess = false;
		return tempID;
	}
	return LevelId::CaveInt;
}

void CaveInt::Draw()
{
	level.Draw();
	back.Draw();

	//int start = 0;
	//int end = 5;
	//
	//for (int i = 0; i < caveTunnels.size(); i++)
	//{
	//	if (!caveTunnels[i].visible)
	//	{
	//		start = i + 1;
	//		if (i + 5 < end)
	//			end = i + 5;
	//	}
	//}

	//for (int i = end; i >= start; i--)
	//{
	//	caveTunnels[i].Draw();
	//}

	for (int i = caveTunnels.size() - 1; i >= 0; i--)
	{
		caveTunnels[i].Draw();
	}
}