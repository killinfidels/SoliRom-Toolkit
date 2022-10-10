#include "Bullet.h"

std::vector<std::vector<Bullet*>> Bullet::bullets;

Bullet::Bullet(float _x, float _y, float _angle, float _vel, Allegiance _team)
{
	rect.x = _x;
	rect.y = _y;
	rect.w = 5 * cam.zoom;
	rect.h = 5 * cam.zoom;

	vel = 20 + _vel;
	angle = _angle;

	team = _team;

	if (bullets.size() != Allegiance::ENDOFLIST)
	{
		bullets.emplace_back();
		bullets.emplace_back();
		bullets.emplace_back();
	}

	bullets[team].push_back(this);
	//bullets[NEUTRAL].push_back(this);
}

Bullet::~Bullet()
{
}

void Bullet::BulletUpdate()
{
	rect.x += sin(angle * 3.14159265 / 180) * vel;
	rect.y += -cos(angle * 3.14159265 / 180) * vel;
}

void Bullet::Update()
{
	for (int i = 0; i < bullets.size(); i++)
	{
		for (int z = 0; z < bullets[i].size(); z++)
		{
			bullets[i][z]->BulletUpdate();
		}
	}
}

void Bullet::BulletDraw()
{
	drawRect =
	{
		rect.x - cam.x - rect.w / 2,
		rect.y - cam.y - rect.h / 2,
		rect.w,
		rect.h
	};

	SDL_RenderDrawRectF(App::Get()->GetCurrentWindow()->getSDL_Renderer(), &drawRect);
}

void Bullet::Draw()
{
	for (int i = 0; i < bullets.size(); i++)
	{
		for (int z = 0; z < bullets[i].size(); z++)
		{
			bullets[i][z]->BulletDraw();
		}
	}
}

bool Bullet::CheckCollision(SDL_FRect _rect, Allegiance _team)
{
	bool flag = false;
	Allegiance type;

	switch (_team)
	{
	case FRIEND:
		type = ENEMY;
		break;
	case ENEMY:
		type = FRIEND;
		break;
	case NEUTRAL:
		type = NEUTRAL;
		break;
	default:
		break;
	}


	for (int i = 0; i < bullets[type].size(); i++)
	{
		if (SDL_HasIntersectionF(&bullets[type][i]->rect, &_rect))
		{
			flag = true;

			delete bullets[type][i];
			bullets[type].erase(bullets[type].begin() + i);
			break;
		}
	}

	return flag;
}

void Bullet::BindToRect(SDL_FRect _rect)
{
	for (int i = 0; i < bullets.size(); i++)
	{
		for (int z = 0; z < bullets[i].size(); z++)
		{
			if (!SDL_HasIntersectionF(&bullets[i][z]->rect, &_rect))
			{
				delete bullets[i][z];
				bullets[i].erase(bullets[i].begin() + z);
				break;
			}
		}
	}
}
