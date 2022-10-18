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

ShackExt::ShackExt() : player(1942, 914, 1)
{
	levelIdentification = LevelId::ShackExt;

	cam.w = w_game->getWidth();
	cam.h = w_game->getHeight();

	//exterior
	t_levelBG = assetManager->createTexture("assets/Shack Exterior HD.png");
	t_levelFG = nullptr;
	t_arrow = assetManager->createTexture("assets/Arrow.png");

	levelBG.SetTexture(t_levelBG);
	right.SetTexture(t_arrow);
	left.SetTexture(t_arrow);

	rescale = cam.h / t_levelBG->GetSize().h;

	levelBG.SetSize(t_levelBG->GetSize().w, t_levelBG->GetSize().h);
	ScaleRect(levelBG.GetRect(), rescale);
	levelBG.UpdateRect();
	right.SetSize(128, 128);
	left.SetSize(128, 128);


	door.SetRect(3565, 1182, 211, 432);
	ScaleRect(door.GetRect(), rescale);
	door.UpdateRect();
	door.SetPos(1897, 629);

	right.SetPos(w_game->getWidth() - right.GetRect()->w, (w_game->getHeight() / 2) - (right.GetRect()->h / 2));
	left.SetPos(0, right.GetRect()->y);

	door.SetCam(&cam);
	levelBG.SetCam(&cam);

	player.SetCam(&cam);
	//rest
}

void ShackExt::Load(LevelId _previousLevel)
{
	if (!loadSuccess)
	{
		loadSuccess = true;

		farts.clear();

		farts.emplace_back(1872, 2056, 4504, 268);
		farts.emplace_back(6248, 2080, -304, -132);
		farts.emplace_back(5960, 2012, -236, -108);
		farts.emplace_back(5736, 1940, 84, -12);
		farts.emplace_back(5752, 1912, 568, -104);
		farts.emplace_back(6188, 1836, 172, -120);
		farts.emplace_back(5792, 1864, -100, -124);
		farts.emplace_back(5740, 1824, 48, 108);
		farts.emplace_back(5724, 1832, 96, 124);
		farts.emplace_back(1872, 2112, 152, -228);
		farts.emplace_back(2012, 1996, -444, -112);
		farts.emplace_back(1556, 1884, 104, 256);
		farts.emplace_back(1652, 2124, -624, -96);
		farts.emplace_back(1016, 2052, 192, -100);
		farts.emplace_back(1200, 1932, 288, -96);
		farts.emplace_back(1180, 1980, 176, -56);
		farts.emplace_back(1236, 1868, -124, -44);
		farts.emplace_back(1216, 1880, -148, -68);
		farts.emplace_back(1080, 1852, -52, -96);
		farts.emplace_back(1116, 1816, -56, -56);
		farts.emplace_back(1048, 1792, -80, -40);
		farts.emplace_back(3448, 2268, -532, 324);
		farts.emplace_back(2956, 2372, -120, 152);
		farts.emplace_back(2860, 2416, -108, 132);
		farts.emplace_back(3376, 2108, 300, -132);
		farts.emplace_back(3352, 2136, 16, -4);

		for (int i = 0; i < farts.size(); i++)
		{
			ScaleRect(&farts[i], rescale);
		}

		enteringDoorFlag = false;
		loadingFade = 0;
		loadingTimer.Stop();
		loadingTimer.Reset();

		player.SetPos(1942, 914);

		player.SetDirection(Player::DOWN);
	}
}

void ShackExt::Script()
{
	if (loadSuccess)
	{
		//if enter door disables controls
		if (!BindToRect(player.GetCollisionRect(), door.GetRect(), false) && loadingTimer.elapsed() == 0)
		{
			enteringDoorFlag = true;
			player.SetPos(player.GetPos()->x, door.GetRect()->y + door.GetRect()->h);
			player.Walk(Player::RIGHT, 0.5);
		}

		if (!enteringDoorFlag)
		{
			player.Controls();
		}

		player.Update();

		//set cam to player pos
		cam.x = player.GetPos()->x - cam.w / 2;
		cam.y = player.GetPos()->y - cam.h / 2;


		//bind cam to inside level bg
		if (cam.x < levelBG.GetRect()->x)
			cam.x = levelBG.GetRect()->x;
		if (cam.y < levelBG.GetRect()->y)
			cam.y = levelBG.GetRect()->y;
		if (cam.x + cam.w > levelBG.GetRect()->x + levelBG.GetRect()->w)
			cam.x = levelBG.GetRect()->x + levelBG.GetRect()->w - cam.w;
		if (cam.y + cam.h > levelBG.GetRect()->y + levelBG.GetRect()->h)
			cam.y = levelBG.GetRect()->y + levelBG.GetRect()->h - cam.h;

		//printf("cam x:%f y:%f\n", cam.x, cam.y);
		
		if (SoliRom::Input::Click())
		{
			printf("klikkworldpos:%i, %i\n",
				(int)(SoliRom::Input::getMouse().x + cam.x),
				(int)(SoliRom::Input::getMouse().y + cam.y));
		}
	}
}


Level::LevelId ShackExt::LevelTransition()
{
	LevelId tempID = levelIdentification;
	if (SoliRom::Input::Click())
	{
		if (SoliRom::Input::MouseInRect(door.GetScreenRect()))
			tempID = LevelId::ShackInt;

		if (SoliRom::Input::MouseInRect(left.GetScreenRect()))
			tempID = LevelId::CaveExt;
	}

	//load if entering door
	if (enteringDoorFlag && BindToRect(player.GetCollisionRect(), door.GetRect(), true))
	{
		loadingTimer.Start();
		loadingTimer.update();

		loadingFade = loadingTimer.elapsed() * 255;

		if (loadingTimer.checkElapsed(1000))
		{
			tempID = LevelId::ShackInt;
		}
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
	levelBG.Draw();
	//levelFG.Draw();
	right.Draw();
	left.Draw(SDL_FLIP_HORIZONTAL);
	//door.DrawRect();

	player.DrawRects();

	if (loadingFade != 0)
	{
		SDL_SetRenderDrawColor(w_game->getSDL_Renderer(), 34, 32, 52, loadingFade);
		SDL_RenderFillRectF(w_game->getSDL_Renderer(), levelBG.GetScreenRect());
		SDL_SetRenderDrawColor(w_game->getSDL_Renderer(), 255, 255, 255, 255);
	}
}