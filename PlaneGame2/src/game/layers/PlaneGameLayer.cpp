#include "PlaneGameLayer.h"

GameLayer::GameLayer() : Layer("PlaneGame")
{
	//system init
	game = App::Get();
	game->SetUpdateTick(20);

	w_game = game->CreateWindow("911 BUNGHOLE GAME", 800, 800);
	SDL_MaximizeWindow(w_game->getSDL_Window());
	SDL_SetWindowFullscreen(w_game->getSDL_Window(), SDL_WINDOW_FULLSCREEN_DESKTOP);

	assetM = AssetManager::Get();
	assetM->setWindow(w_game);

	//cam init
	cam.w = w_game->getWidth();
	cam.h = w_game->getHeight();

	//player init
	player = new Player;
	player->SetCam(&cam);

	//map init
	float mapScale = 2.5;
	t_map = assetM->createTexture("assets/sea.png");
	map.SetTexture(t_map);
	
	*map.GetRect() = {
		0, 0,
		(float)t_map->GetSize().w * mapScale, (float)t_map->GetSize().w * mapScale
	};
	map.SetCam(&cam);

	Bullet::BindToRect(*map.GetRect());
}

void GameLayer::OnEvent()
{
	if (EventHandler::getQuit() || EventHandler::keyPressed(SDLK_ESCAPE))
	{
		game->Quit();
	}
}

void GameLayer::OnUpdate()
{
	cam.x = player->GetPos()->x - cam.w / 2;
	cam.y = player->GetPos()->y - cam.h / 2;

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

	map.Draw();

	player->PlayerDraw();

	Bullet::Draw();
}