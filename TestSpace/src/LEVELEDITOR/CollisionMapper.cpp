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

	int w, h;
	SDL_QueryTexture(t_map->Get(), NULL, NULL, &w, &h);

	//temp
	float ratio = w / h;
	if (w > 1900)
	{
		scale = w / 1900;
		w = 1900;
		h = 1900 / ratio;
	}

	if (w <= 1900 && h <= 1900)
	{
		SDL_SetWindowSize(w_map->getSDL_Window(), w, h);
	}
	//temp

	g_map.SetTexture(t_map);
	g_map.setSize(w, h);

	cam.x = 0;
	cam.y = 0;

	w_rect = app->CreateWindow("rects", 10, 10);
	SoliRom::AssetManager::Get()->setWindow(w_rect);

	SDL_Color poo;
	poo = {
		0, 0, 0, 255
	};

	t_text = SoliRom::AssetManager::Get()->createTextureFromText("poo", 100, poo);

	SDL_QueryTexture(t_text->Get(), NULL, NULL, &w, &h);

	SDL_SetWindowSize(w_rect->getSDL_Window(), w, h);

	g_text.SetTexture(t_text);
	g_text.setSize(w, h);

	RectInfo::init();

	SoliRom::AssetManager::Get()->setWindow(w_map);
}

void CollisionMapper::OnEvent()
{
	if (SoliRom::EventHandler::keyPressed(SDLK_ESCAPE))
	{
		app->Quit();
	}

	if (SoliRom::EventHandler::keyPressed(SDLK_s) && !saveToggle)
	{
		save();
		saveToggle = true;
	}
	
	if (!SoliRom::EventHandler::keyPressed(SDLK_s))
	{
		saveToggle = false;
	}

	if (SoliRom::EventHandler::click() && !creating && SoliRom::EventHandler::getMouse().window == w_map)
	{
		creating = true;
		clickWorldPosX = SoliRom::EventHandler::getMouse().x + cam.x;
		clickWorldPosY = SoliRom::EventHandler::getMouse().y + cam.y;

		//temp scale
		farts.emplace_back(clickWorldPosX * scale, clickWorldPosY * scale, 0, 0);
	}

	if (SoliRom::EventHandler::getMouse().state == SoliRom::HELD && creating)
	{
		clickWorldPosX = SoliRom::EventHandler::getMouse().x + cam.x;
		clickWorldPosY = SoliRom::EventHandler::getMouse().y + cam.y;

		//temp scale
		farts.back().w = clickWorldPosX * scale - farts.back().x;
		farts.back().h = clickWorldPosY * scale - farts.back().y;
	}
	else if (SoliRom::EventHandler::getMouse().state == SoliRom::IDLE && creating)
	{
		creating = false;

		SoliRom::AssetManager::Get()->setWindow(w_rect);
		test.push_back(new RectInfo(farts.size() - 1, &farts.back()));
		SoliRom::AssetManager::Get()->setWindow(w_map);
	}
}

void CollisionMapper::OnUpdate()
{
	g_map.setPosition(-cam.x, -cam.y);
	g_map.Draw();
	//g_text.Draw();

	drawFarts = farts;
	SDL_SetRenderDrawColor(w_map->getSDL_Renderer(), 255, 0, 0, 100);
	for (int i = 0; i < drawFarts.size(); i++)
	{
		drawFarts[i].x = farts[i].x - cam.x;
		drawFarts[i].y = farts[i].y - cam.y;

		//temp
		drawFarts[i].x = drawFarts[i].x / scale;
		drawFarts[i].y = drawFarts[i].y / scale;
		drawFarts[i].w = drawFarts[i].w / scale;
		drawFarts[i].h = drawFarts[i].h / scale;
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
		data += "farts.emplace_back("
			+ std::to_string(farts[i].x) + " * rescale, "
			+ std::to_string(farts[i].y) + " * rescale, "
			+ std::to_string(farts[i].w) + " * rescale, "
			+ std::to_string(farts[i].h) + " * rescale);\n";
	}

	SR_WARN(data.c_str());
}
