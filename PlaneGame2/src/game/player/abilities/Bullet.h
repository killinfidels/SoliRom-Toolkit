#pragma once
#include "Core.h"

class Bullet : public EngineObject
{
public:
	Bullet(float _x, float _y, float _angle, float _vel, Allegiance _team);
	~Bullet();

	static void Update();
	static void Draw();
	static bool CheckCollision(SDL_FRect _rect, Allegiance _team);
	static void BindToRect(SDL_FRect _rect);

private:
	static Asset::Texture* bulletTexture;
	static SDL_FRect boundingBox;
	float vel, angle;
	Allegiance team;
	void BulletUpdate();
	void BulletDraw();
	static std::vector<std::vector<Bullet*>> bullets;
};