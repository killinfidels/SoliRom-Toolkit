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

	void AlignFormulas();

	void DrawRects();

	void Update();

	int posX, posY;
private:
	static void InitAssets();

	State state;
	Direction direction;

	static bool loaded;
	static SoliRom::Asset::Animation* a_down;
	static SoliRom::Asset::Animation* a_up;
	static SoliRom::Asset::Animation* a_left;
	static SoliRom::Asset::Animation* a_right;
	static SoliRom::Asset::Texture* t_idle;

	std::vector<SDL_Rect*> levelRects;
	std::vector<SDL_Rect*> wallRects;

	//IMPLEMENT COLLISION RECT AND TEXTURE RECT IN ENGINE
	SDL_Rect collisionBox;
	SDL_Rect interactBox;
	SDL_Rect d_collisionBox;
	SDL_Rect d_interactBox;
};