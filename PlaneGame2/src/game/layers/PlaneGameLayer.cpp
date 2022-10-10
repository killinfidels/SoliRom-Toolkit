#include "PlaneGameLayer.h"

GameLayer::GameLayer() : Layer("PlaneGame")
{
	game = App::Get();
	game->SetUpdateTick(20);
	w_game = game->CreateWindow("911 BUNGHOLE GAME", 800, 800);
	SDL_MaximizeWindow(w_game->getSDL_Window());
	assetM = AssetManager::Get();
	assetM->setWindow(w_game);

	cam.zoom = 2;
	
	player = new Player;

	t_map = assetM->createTexture("assets/sea.png");

	map.SetTexture(t_map);
	SDL_QueryTexture(t_map->Get(), NULL, NULL, &map.GetRect()->w, &map.GetRect()->h);
	map.setSize(map.GetRect()->w / 1 * cam.zoom, map.GetRect()->h / 1 * cam.zoom);

	mapRect = 
	{
		(float)map.GetRect()->x,
		(float)map.GetRect()->y,
		(float)map.GetRect()->w,
		(float)map.GetRect()->h
	};

	fps.Start();
}

void GameLayer::OnEvent()
{
	fps.update();

	if (EventHandler::getQuit())
	{
		game->Quit();
	}
}

void GameLayer::OnUpdate()
{
	cam.w = w_game->getWidth();
	cam.h = w_game->getHeight();
	cam.x = player->rect.x - cam.w / 2;
	cam.y = player->rect.y - cam.h / 2;
	if (cam.x < 0)
		cam.x = 0;
	if (cam.y < 0)
		cam.y = 0;
	if (cam.x + cam.w > map.GetRect()->w)
		cam.x = map.GetRect()->w - cam.w;
	if (cam.y + cam.h > map.GetRect()->h)
		cam.y = map.GetRect()->h - cam.h;

	Bullet::Update();

	player->Update();

	map.setPosition(-cam.x, -cam.y);

	Bullet::BindToRect(mapRect);

	map.Draw();

	player->PlayerDraw();

	Bullet::Draw();
}