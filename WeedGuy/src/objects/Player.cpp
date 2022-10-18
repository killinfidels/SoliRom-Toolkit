#include "Player.h"

bool Player::loaded = false;
SoliRom::Asset::Animation* Player::a_down;
SoliRom::Asset::Animation* Player::a_up;
SoliRom::Asset::Animation* Player::a_left;
SoliRom::Asset::Animation* Player::a_right;
SoliRom::Asset::Texture* Player::t_downIdle;
SoliRom::Asset::Texture* Player::t_upIdle;
SoliRom::Asset::Texture* Player::t_leftIdle;
SoliRom::Asset::Texture* Player::t_rightIdle;

void Player::InitAssets()
{
	a_down = SoliRom::AssetManager::Get()->createAnimation("assets/down_1.png");
	a_up = SoliRom::AssetManager::Get()->createAnimation("assets/up_1.png");
	a_left = SoliRom::AssetManager::Get()->createAnimation("assets/left_1.png");
	a_right = SoliRom::AssetManager::Get()->createAnimation("assets/right_1.png");
	t_downIdle = SoliRom::AssetManager::Get()->createTexture("assets/downIdle.png");
	t_upIdle = SoliRom::AssetManager::Get()->createTexture("assets/upIdle.png");
	t_leftIdle = SoliRom::AssetManager::Get()->createTexture("assets/leftIdle.png");
	t_rightIdle = SoliRom::AssetManager::Get()->createTexture("assets/rightIdle.png");

	int frametime = 250;
	a_down->SetFrametime(frametime);
	a_up->SetFrametime(frametime);
	a_left->SetFrametime(frametime);
	a_right->SetFrametime(frametime);

	loaded = true;
}

Player::Player(int _x, int _y, int _scale)
{
	state = STAND;
	direction = DOWN;

	SetPos(_x, _y);

	if (!loaded)
		InitAssets();

	int w, h;
	SDL_QueryTexture(t_downIdle->Get(), NULL, NULL, &w, &h);
	w /= 1.5;
	h /= 1.5;
	SetSize(w, h);
	SetOffset(-w / 2.0, -h + 10);
	centre = { pos.x, pos.y - h / 2 };

	collisionBox.w = 40;
	collisionBox.h = 15;
	d_collisionBox.w = collisionBox.w;
	d_collisionBox.h = collisionBox.h;

	collisionBox.x = pos.x - collisionBox.w / 2;
	collisionBox.y = pos.y - collisionBox.h;

	interactBox.w = 80;
	interactBox.h = 80;
	d_interactBox.w = interactBox.w;
	d_interactBox.h = interactBox.h;

	speed = 4;
}

void Player::Update()
{
	centre = { pos.x, pos.y - GetRect()->h / 2 };

	collisionBox.x = pos.x - collisionBox.w / 2;
	collisionBox.y = pos.y - collisionBox.h;

	switch (direction)
	{
	case Player::DOWN:
		interactBox.x = collisionBox.x + collisionBox.w / 2 - interactBox.w / 2;
		interactBox.y = collisionBox.y + collisionBox.h;
		if (state != WALK)
		{
			a_down->Stop();
			SetTexture(t_downIdle);
		}
		else
		{
			a_down->Start();
			SetTexture(a_down->Get());
		}
		break;
	case Player::UP:
		interactBox.x = collisionBox.x + collisionBox.w / 2 - interactBox.w / 2;
		interactBox.y = collisionBox.y - interactBox.h;
		if (state != WALK)
		{
			a_up->Stop();
			SetTexture(t_upIdle);
		}
		else
		{
			a_up->Start();
			SetTexture(a_up->Get());
		}
		break;
	case Player::LEFT:
		interactBox.x = collisionBox.x - interactBox.w;
		interactBox.y = collisionBox.y + collisionBox.h / 2 - interactBox.h / 2;
		if (state != WALK)
		{
			a_left->Stop();
			SetTexture(t_leftIdle);
		}
		else
		{
			a_left->Start();
			SetTexture(a_left->Get());
		}
		break;
	case Player::RIGHT:
		interactBox.x = collisionBox.x + collisionBox.w;
		interactBox.y = collisionBox.y + collisionBox.h / 2 - interactBox.h / 2;
		if (state != WALK)
		{
			a_right->Stop();
			SetTexture(t_rightIdle);
		}
		else
		{
			a_right->Start();
			SetTexture(a_right->Get());
		}
		break;
	default:
		break;
	}

	state = STAND;
}

void Player::SetDirection(Direction _direction)
{
	direction = _direction;
}

void Player::DrawRects()
{
	d_collisionBox.x = collisionBox.x - cam->x;
	d_collisionBox.y = collisionBox.y - cam->y;

	d_interactBox.x = interactBox.x - cam->x;
	d_interactBox.y = interactBox.y - cam->y;

	centreScreen = { centre.x - cam->x, centre.y - cam->y };

	Draw();

	//DrawRect();

	//SDL_SetRenderDrawColor(SoliRom::App::Get()->GetCurrentWindow()->getSDL_Renderer(), 255, 0, 0, 255);
	//
	//SDL_RenderDrawRectF(SoliRom::App::Get()->GetCurrentWindow()->getSDL_Renderer(), &d_collisionBox);
	//SDL_RenderDrawRectF(SoliRom::App::Get()->GetCurrentWindow()->getSDL_Renderer(), &d_interactBox);
	//
	//SDL_SetRenderDrawColor(SoliRom::App::Get()->GetCurrentWindow()->getSDL_Renderer(), 0, 0, 255, 255);
	//SDL_RenderDrawPointF(SoliRom::App::Get()->GetCurrentWindow()->getSDL_Renderer(), screenPos.x, screenPos.y);
	//SDL_RenderDrawPointF(SoliRom::App::Get()->GetCurrentWindow()->getSDL_Renderer(), centreScreen.x, centreScreen.y);
	//
	//SDL_SetRenderDrawColor(SoliRom::App::Get()->GetCurrentWindow()->getSDL_Renderer(), 255, 255, 255, 255);

}

void Player::Controls()
{
	if (SoliRom::Input::keyPressed(SDLK_w) || SoliRom::Input::keyPressed(SDLK_UP))
	{
		Walk(UP);
	}

	if (SoliRom::Input::keyPressed(SDLK_s) || SoliRom::Input::keyPressed(SDLK_DOWN))
	{
		Walk(DOWN);
	}

	if (SoliRom::Input::keyPressed(SDLK_a) || SoliRom::Input::keyPressed(SDLK_LEFT))
	{
		Walk(LEFT);
	}

	if (SoliRom::Input::keyPressed(SDLK_d) || SoliRom::Input::keyPressed(SDLK_RIGHT))
	{
		Walk(RIGHT);
	}
}

void Player::Walk(Direction _direction)
{
	Walk(_direction, speed);
}

void Player::Walk(Direction _direction, float _speed)
{
	switch (_direction)
	{
	case Player::DOWN:
		Move(0, _speed);
		direction = DOWN;
		state = WALK;
		break;
	case Player::UP:
		Move(0, -_speed);
		direction = UP;
		state = WALK;
		break;
	case Player::LEFT:
		Move(-_speed, 0);
		direction = LEFT;
		state = WALK;
		break;
	case Player::RIGHT:
		Move(_speed, 0);
		direction = RIGHT;
		state = WALK;
		break;
	default:
		break;
	}
}

SDL_FRect* Player::GetCollisionRect()
{
	return &collisionBox;
}
