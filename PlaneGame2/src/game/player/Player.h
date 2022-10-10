#include "Core.h"
#include "abilities/Bullet.h"

class Player : public GameObject
{
public:
	Player();
	~Player();

	void Update();
	void Controls();
	void Shoot();
	void PlayerDraw();

	SDL_FRect rect;
private:
	Asset::Animation* a_player;
	Asset::Animation* a_explosion;
	Asset::Animation* a_gunfire;

	SDL_FRect drawRect;

	SDL_FPoint gun;
	SDL_FPoint gunTranslated;
	Timer spaceTimer;

	float velocity;
	float acceleration;
	float angle;
	float maxV, minV;
};

