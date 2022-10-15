#include "Player.h"

bool Player::loaded = false;
SoliRom::Asset::Animation* Player::a_down;
SoliRom::Asset::Animation* Player::a_up;
SoliRom::Asset::Animation* Player::a_left;
SoliRom::Asset::Animation* Player::a_right;
SoliRom::Asset::Texture* Player::t_idle;

void Player::InitAssets()
{
	a_down = SoliRom::AssetManager::Get()->createAnimation("assets/down_1.png");
	a_up = SoliRom::AssetManager::Get()->createAnimation("assets/up_1.png");
	a_left = SoliRom::AssetManager::Get()->createAnimation("assets/left_1.png");
	a_right = SoliRom::AssetManager::Get()->createAnimation("assets/right_1.png");
	t_idle = SoliRom::AssetManager::Get()->createTexture("assets/idle.png");

	loaded = true;
}

Player::Player(int _x, int _y, int _scale)
{
	state = STAND;
	direction = DOWN;

	posX = _x;
	posY = _y;

	collisionBox.w = 100;
	collisionBox.h = 100;
	d_collisionBox.w = collisionBox.w;
	d_collisionBox.h = collisionBox.h;

	collisionBox.x = posX - collisionBox.w / 2;
	collisionBox.y = posY - collisionBox.h / 2;

	if (!loaded)
		InitAssets();

	int w, h;
	SDL_QueryTexture(t_idle->Get(), NULL, NULL, &w, &h);
	w /= 1.5;
	h /= 1.5;
	setSize(w, h);
	setPosition(posX - GetRect()->w / 2, GetRect()->y - h / 2);

	interactBox.w = 80;
	interactBox.h = 80;
	d_interactBox.w = interactBox.w;
	d_interactBox.h = interactBox.h;
}

void Player::Update()
{
	int speed = 3;

	state = STAND;

	if (SoliRom::EventHandler::keyPressed(SDLK_w) || SoliRom::EventHandler::keyPressed(SDLK_UP))
	{
		posY -= speed;
		direction = UP;
		state = WALK;
	}

	if (SoliRom::EventHandler::keyPressed(SDLK_s) || SoliRom::EventHandler::keyPressed(SDLK_DOWN))
	{
		posY += speed;
		direction = DOWN;
		state = WALK;
	}

	if (SoliRom::EventHandler::keyPressed(SDLK_a) || SoliRom::EventHandler::keyPressed(SDLK_LEFT))
	{
		posX -= speed;
		direction = LEFT;
		state = WALK;
	}

	if (SoliRom::EventHandler::keyPressed(SDLK_d) || SoliRom::EventHandler::keyPressed(SDLK_RIGHT))
	{
		posX += speed;
		direction = RIGHT;
		state = WALK;
	}

	switch (direction)
	{
	case Player::DOWN:
		interactBox.y = collisionBox.y + collisionBox.h;
		interactBox.x = collisionBox.x + collisionBox.w / 2 - interactBox.w / 2;
		if (state != WALK)
		{
			a_down->Stop();
			SetTexture(t_idle);
		}
		else
		{
			a_down->Start();
			SetTexture(a_down->Get());
		}
		break;
	case Player::UP:
		interactBox.y = collisionBox.y - interactBox.h;
		interactBox.x = collisionBox.x + collisionBox.w / 2 - interactBox.w / 2;
		if (state != WALK)
			a_up->Stop();
		else
			a_up->Start();
		SetTexture(a_up->Get());
		break;
	case Player::LEFT:
		interactBox.x = collisionBox.x - interactBox.w;
		interactBox.y = collisionBox.y + collisionBox.h / 2 - interactBox.h / 2;
		if (state != WALK)
			a_left->Stop();
		else
			a_left->Start();
		SetTexture(a_left->Get());
		break;
	case Player::RIGHT:
		interactBox.x = collisionBox.x + collisionBox.w;
		interactBox.y = collisionBox.y + collisionBox.h / 2 - interactBox.h / 2;
		if (state != WALK)
			a_right->Stop();
		else
			a_right->Start();
		SetTexture(a_right->Get());
		break;
	default:
		break;
	}

	setPosition(posX - GetRect()->w / 2 - cam.x, posY - GetRect()->h / 2 - cam.y);

	collisionBox.x = posX - collisionBox.w / 2;
	collisionBox.y = posY - collisionBox.h / 2;

	d_collisionBox.x = collisionBox.x - cam.x;
	d_collisionBox.y = collisionBox.y - cam.y;

	d_interactBox.x = interactBox.x - cam.x;
	d_interactBox.y = interactBox.y - cam.y;
}

void Player::DrawRects()
{
	Draw();

	DrawRect(true);

	SDL_SetRenderDrawColor(SoliRom::App::Get()->GetCurrentWindow()->getSDL_Renderer(), 255, 0, 0, 255);

	SDL_RenderDrawRect(SoliRom::App::Get()->GetCurrentWindow()->getSDL_Renderer(), &d_collisionBox);
	SDL_RenderDrawRect(SoliRom::App::Get()->GetCurrentWindow()->getSDL_Renderer(), &d_interactBox);
	SDL_RenderDrawPoint(SoliRom::App::Get()->GetCurrentWindow()->getSDL_Renderer(), posX - cam.x, posY - cam.y);

	SDL_SetRenderDrawColor(SoliRom::App::Get()->GetCurrentWindow()->getSDL_Renderer(), 255, 255, 255, 255);

}