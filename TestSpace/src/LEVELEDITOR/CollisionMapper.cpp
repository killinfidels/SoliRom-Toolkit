#include "CollisionMapper.h"

//MAKE COLLISONS RELATIVE -- UX CORDINATER
CollisionMapper::CollisionMapper() : Layer("Collision Mapping Layer")
{
	SR_TRACE("CollisionMapper IS HERE!");

	app = SoliRom::App::Get();

	bool mapLoad;

	do
	{
		mapLoad = true;

		SR_INFO("Input map texture relpath:");
	
		//switch these two when done testing
		mapPath = "assets/Shack Exterior HD.png";
		//mapPath = "assets/idle_1.png";
		//std::getline(std::cin, mapPath);

		if (!SDL_RWFromFile(mapPath.c_str(), "r"))
		{
			SR_ERROR("File does not exist! Path: %s", mapPath.c_str());
			mapLoad = false;
		}

	} while (!mapLoad);

	SR_INFO("Input a name for your collision map");

	//switch these two when done testing
	collisionMapName = "Road";
	//std::getline(std::cin, collisionMapName);

	w_map = app->CreateWindow(mapPath.substr(mapPath.rfind("/") + 1, mapPath.rfind(".") - mapPath.rfind("/") - 1) + " : " + collisionMapName + " Collisons", 400, 0);

	SoliRom::AssetManager::Get()->setWindow(w_map);
	t_map = SoliRom::AssetManager::Get()->createTexture(mapPath);

	if (t_map->GetSize().w > 1900 || t_map->GetSize().h > 900)
	{
		if (t_map->GetSize().w / 1900.0 > t_map->GetSize().h / 900.0)
		{
			cam.scale = 1900.0 / t_map->GetSize().w;
		}
		else
		{
			cam.scale = 900.0 / t_map->GetSize().h;
		}
	}

	g_map.SetSize(t_map->GetSize().w * cam.scale, t_map->GetSize().h * cam.scale);
	g_map.SetTexture(t_map);

	SDL_SetWindowSize(w_map->getSDL_Window(), g_map.GetRect()->w, g_map.GetRect()->h);

	cam.x = 0;
	cam.y = 0;

	w_rect = app->CreateWindow("rects", 10, 10);
	SoliRom::AssetManager::Get()->setWindow(w_rect);

	SDL_Color poo;
	poo = {
		0, 0, 0, 255
	};

	t_text = SoliRom::AssetManager::Get()->createTextureFromText("poo", 100, poo);

	SDL_SetWindowSize(w_rect->getSDL_Window(), t_text->GetSize().w, t_text->GetSize().h);

	g_text.SetTexture(t_text);
	g_text.SetSize(t_text->GetSize().w, t_text->GetSize().h);

	RectInfo::init();

	SoliRom::AssetManager::Get()->setWindow(w_map);
}

void CollisionMapper::OnEvent()
{
	if (SoliRom::Input::keyPressed(SDLK_ESCAPE) || SoliRom::Input::getQuit())
	{
		app->Quit();
	}

	if (SoliRom::Input::keyPressed(SDLK_s) && !saveToggle)
	{
		save();
		saveToggle = true;
	}
	
	if (!SoliRom::Input::keyPressed(SDLK_s))
	{
		saveToggle = false;
	}

	if (SoliRom::Input::Click() && !creating && SoliRom::Input::getMouse().window == w_map)
	{
		creating = true;
		clickWorldPosX = SoliRom::Input::getMouse().x + cam.x;
		clickWorldPosY = SoliRom::Input::getMouse().y + cam.y;

		//temp cam.scale
		farts.emplace_back(clickWorldPosX * 1 / cam.scale, clickWorldPosY * 1 / cam.scale, 0, 0);
	}

	if (SoliRom::Input::getMouse().state == SoliRom::HELD && creating)
	{
		clickWorldPosX = SoliRom::Input::getMouse().x + cam.x;
		clickWorldPosY = SoliRom::Input::getMouse().y + cam.y;

		//temp cam.scale
		farts.back().w = clickWorldPosX * 1 / cam.scale - farts.back().x;
		farts.back().h = clickWorldPosY * 1 / cam.scale - farts.back().y;
	}
	else if (SoliRom::Input::getMouse().state == SoliRom::IDLE && creating)
	{
		creating = false;

		SoliRom::AssetManager::Get()->setWindow(w_rect);
		test.push_back(new RectInfo(farts.size() - 1, &farts.back()));
		SoliRom::AssetManager::Get()->setWindow(w_map);
	}
}

void CollisionMapper::OnUpdate()
{
	*g_map.GetPos() = { (float)-cam.x, (float)-cam.y};
	g_map.UpdatePos();

	g_map.Draw();
	//g_text.Draw();

	drawFarts = farts;
	SDL_SetRenderDrawColor(w_map->getSDL_Renderer(), 255, 0, 0, 100);
	for (int i = 0; i < drawFarts.size(); i++)
	{
		drawFarts[i].x = farts[i].x - cam.x;
		drawFarts[i].y = farts[i].y - cam.y;

		//temp
		drawFarts[i].x = drawFarts[i].x * cam.scale;
		drawFarts[i].y = drawFarts[i].y * cam.scale;
		drawFarts[i].w = drawFarts[i].w * cam.scale;
		drawFarts[i].h = drawFarts[i].h * cam.scale;
		//temp

		SDL_RenderDrawRect(w_map->getSDL_Renderer(), &drawFarts[i]);
	}
	SDL_SetRenderDrawColor(w_map->getSDL_Renderer(), 255, 255, 255, 255);

	for (int i = 0; i < test.size(); i++)
	{
		test[i]->draw();
	}
}

void CollisionMapper::save()
{
	std::string data = "\n";
	for (int i = 0; i < farts.size(); i++)
	{
		data += ""
			+ std::to_string(farts[i].x) + ", "
			+ std::to_string(farts[i].y) + ", "
			+ std::to_string(farts[i].w) + ", "
			+ std::to_string(farts[i].h) + "\n";
	}

	SR_WARN(data.c_str());
}
