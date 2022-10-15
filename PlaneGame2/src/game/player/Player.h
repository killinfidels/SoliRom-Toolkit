#include "Core.h"
#include "abilities/Bullet.h"

class Player : public EngineObject
{
public:
	Player();
	~Player();

	void Update();
	void Controls();
	void Shoot();
	void PlayerDraw();

private:
	Asset::Animation* a_player;
	Asset::Animation* a_explosion;
	Asset::Animation* a_gunfire;

	SDL_FPoint gun;
	Timer shootCooldown;

	float velocity;
	float acceleration;
	float angle;
	float maxV, minV;
};

