#include "Player.h"


Player::Player()
{
	a_player = AssetManager::Get()->createAnimation("assets/plane2_1.png", 50);
	a_explosion = AssetManager::Get()->createAnimation("assets/explosion_1.png", 100);
	a_gunfire = AssetManager::Get()->createAnimation("assets/gunfire_1.png", 100);

	int tempW, tempH;
	SDL_QueryTexture(a_player->Get()->Get(), NULL, NULL, &tempW, &tempH);
	rect.w = tempW * 1.25 * cam.zoom;
	rect.h = tempH * 1.25 * cam.zoom;

	rect.x = ((App::Get()->GetCurrentWindow()->getWidth() - rect.w) / 2) * cam.zoom;
	rect.y = ((App::Get()->GetCurrentWindow()->getHeight() - rect.h) / 2) * cam.zoom;

	gun.x = 0;
	gun.y = -rect.h / 2;

	angle = 0;
	acceleration = 0.2;
	velocity = 0;

	maxV = 10;
	minV = 3;


	a_player->Start();
	spaceTimer.Start();
}

Player::~Player()
{
}

void Player::Update()
{
	if (EventHandler::keyPressed(SDLK_RIGHT) || EventHandler::keyPressed(SDLK_d))
		angle += 1 / (velocity * 1.5 / maxV);
	if (EventHandler::keyPressed(SDLK_LEFT) || EventHandler::keyPressed(SDLK_a))
		angle -= 1 / (velocity * 1.5 / maxV);
	if (angle > 360)
		angle -= 360;
	if (angle < 0)
		angle += 360;

	if (EventHandler::keyPressed(SDLK_UP) || EventHandler::keyPressed(SDLK_w))
		velocity += acceleration;
	if (EventHandler::keyPressed(SDLK_DOWN) || EventHandler::keyPressed(SDLK_s))
		velocity -= acceleration;
	if (velocity > maxV)
		velocity = maxV;
	if (velocity < minV)
		velocity = minV;

	rect.x += sin(angle * 3.14159265 / 180) * velocity;
	rect.y += -cos(angle * 3.14159265 / 180) * velocity;

	if (rect.x < cam.x - rect.h * 4 || rect.x >  cam.x + cam.w + rect.h * 4)
	{
		angle -= 180;
	}

	if (rect.y < cam.y - rect.h * 4 || rect.y >  cam.y + cam.h + rect.h * 4)
	{
		angle -= 180;
	}
	
	spaceTimer.update();

	if (EventHandler::keyPressed(SDLK_SPACE) && spaceTimer.checkElapsed(200))
	{
		spaceTimer.Reset();
		gunTranslated.x = rect.x + gun.y * -sin(angle * 3.14159265 / 180);
		gunTranslated.y = rect.y + gun.y * cos(angle * 3.14159265 / 180);
		new Bullet(gunTranslated.x, gunTranslated.y, angle, velocity, FRIEND);
	}
}


void Player::PlayerDraw()
{
	Window* w_game = App::Get()->GetCurrentWindow();

	drawRect =
	{
		rect.x - cam.x - rect.w / 2,
		rect.y - cam.y - rect.h / 2,
		rect.w,
		rect.h
	};

	SDL_RenderCopyExF(w_game->getSDL_Renderer(), a_player->Get()->Get(), NULL, &drawRect, angle, NULL, SDL_FLIP_NONE);
}
