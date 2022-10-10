#pragma once
#include "Core.h"

class Bullet
{
public:
	Bullet(float _x, float _y, float _angle, float _vel, Allegiance _team);
	~Bullet();

	static void Update();
	static void Draw();
	static bool CheckCollision(SDL_FRect _rect, Allegiance _team);
	static void BindToRect(SDL_FRect _rect);

private:
	//Asset::Texture* bulletTexture;
	SDL_FRect rect;
	SDL_FRect drawRect;
	float vel, angle;
	Allegiance team;
	void BulletUpdate();
	void BulletDraw();
	static std::vector<std::vector<Bullet*>> bullets;
};