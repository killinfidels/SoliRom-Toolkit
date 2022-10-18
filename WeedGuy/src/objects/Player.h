#include "core.h"
#include "Object.h"

class Player : public Object
{
public:
	Player(int _x, int _y, int _scale);

	enum Direction
	{
		DOWN,
		UP,
		LEFT,
		RIGHT
	};

	enum State
	{
		STAND,
		WALK,
		TALK
	};

	void SetDirection(Direction _direction);

	void AddLevelRect(SDL_Rect* _rect);
	void AddWallRect(SDL_Rect* _rect);

	//for collision offsets
	void AlignFormulas();

	void DrawRects();

	void Controls();

	void Update();

	void Walk(Direction _direction);
	void Walk(Direction _direction, float _speed);

	SDL_FRect* GetCollisionRect();
private:
	static void InitAssets();

	State state;
	Direction direction;

	static bool loaded;
	static SoliRom::Asset::Animation* a_down;
	static SoliRom::Asset::Animation* a_up;
	static SoliRom::Asset::Animation* a_left;
	static SoliRom::Asset::Animation* a_right;
	static SoliRom::Asset::Texture* t_downIdle;
	static SoliRom::Asset::Texture* t_upIdle;
	static SoliRom::Asset::Texture* t_leftIdle;
	static SoliRom::Asset::Texture* t_rightIdle;

	std::vector<SDL_Rect*> levelRects;
	std::vector<SDL_Rect*> wallRects;

	//IMPLEMENT COLLISION RECT AND TEXTURE RECT IN ENGINE
	SDL_FPoint centre, centreScreen;
	SDL_FRect collisionBox;
	SDL_FRect interactBox;
	SDL_FRect d_collisionBox;
	SDL_FRect d_interactBox;

	float speed;
};