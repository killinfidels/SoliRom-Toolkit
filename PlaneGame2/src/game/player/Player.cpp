#include "Player.h"


Player::Player()
{
	a_player = AssetManager::Get()->createAnimation("assets/plane2_1.png", 50);
	a_explosion = AssetManager::Get()->createAnimation("assets/explosion_1.png", 100);
	a_gunfire = AssetManager::Get()->createAnimation("assets/gunfire_1.png", 100);

	rect.w = a_player->Get()->GetSize().w * 2;
	rect.h = a_player->Get()->GetSize().h * 2;

	pos.x = App::Get()->GetCurrentWindow()->getWidth() / 2;
	pos.y = App::Get()->GetCurrentWindow()->getHeight() / 2;

	UpdatePos();

	offset.x = -rect.w / 2;
	offset.y = -rect.h / 2;

	UpdateOffset();

	gun.x = 0;
	gun.y = -rect.h / 2;

	angle = 0;
	acceleration = 0.2;
	velocity = 0;

	maxV = 10;
	minV = 3;

	a_player->Start();
	shootCooldown.Start();
}

Player::~Player()
{
}

void Player::Update()
{
	if (Input::keyPressed(SDLK_RIGHT) || Input::keyPressed(SDLK_d))
		angle += 1 / (velocity * 1.5 / maxV);
	if (Input::keyPressed(SDLK_LEFT) || Input::keyPressed(SDLK_a))
		angle -= 1 / (velocity * 1.5 / maxV);
	if (angle > 360)
		angle -= 360;
	if (angle < 0)
		angle += 360;

	if (Input::keyPressed(SDLK_UP) || Input::keyPressed(SDLK_w))
		velocity += acceleration;
	if (Input::keyPressed(SDLK_DOWN) || Input::keyPressed(SDLK_s))
		velocity -= acceleration;
	if (velocity > maxV)
		velocity = maxV;
	if (velocity < minV)
		velocity = minV;

	pos.x += sin(angle * 3.14159265 / 180) * velocity;
	pos.y += -cos(angle * 3.14159265 / 180) * velocity;

	UpdatePos();

	//flip if player goes outside camera - camera stops at map borders :)
	if (pos.x < cam->x - rect.h * 4 || pos.x >  cam->x + cam->w + rect.h * 4)
	{
		angle -= 180;
	}

	if (pos.y < cam->y - rect.h * 4 || pos.y >  cam->y + cam->h + rect.h * 4)
	{
		angle -= 180;
	}
	
	shootCooldown.update();

	if (Input::keyPressed(SDLK_SPACE) && shootCooldown.checkElapsed(200))
	{
		shootCooldown.Reset();
		//angle = 90;
		float test = sin(angle * 3.14159265 / 180);
		SDL_FPoint tempGunTranslated = {
			pos.x + gun.x * cos(angle * 3.14159265 / 180) + gun.y * -sin(angle * 3.14159265 / 180),
			pos.y + gun.y * cos(angle * 3.14159265 / 180) + gun.x * sin(angle * 3.14159265 / 180),
		};

		Bullet* bullet = new Bullet(tempGunTranslated.x, tempGunTranslated.y, angle, velocity, FRIEND);
		bullet->SetCam(cam);
		bullet = nullptr;
	}
}


void Player::PlayerDraw()
{
	SDL_Renderer* renderer = a_player->Get()->GetWindow()->getSDL_Renderer();

	UpdateScreenPositions();

	texture = a_player->Get();

	SDL_RenderCopyExF(renderer, texture->Get(), NULL, &screenRect, angle, NULL, SDL_FLIP_NONE);
}
