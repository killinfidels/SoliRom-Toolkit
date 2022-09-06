#include "core.h"

//SoliRom::App Game(scale);

SoliRom::Texture chip::chip1;
SoliRom::Texture chip::chip2;
SoliRom::Texture chip::chip3;

int chip::heldChip = -1;

Guy::Guy()
{
	sizeMul = 4;
	setSize(100 * sizeMul, 100 * sizeMul);
	setPosition(Game.getWindow()->getWindowWidth() - getRect()->w, (int)(Game.getWindow()->getWindowHeight() / 1.4) - (getRect()->h / 2));

	Idle1.create("Assets/idle_1.png");
	Idle2.create("Assets/idle_2.png");
	Idle3.create("Assets/idle_3.png");
	Pick1.create("Assets/nosepick_1.png");
	Pick2.create("Assets/nosepick_2.png");
	Hungry1.create("Assets/food_1.png");
	Hungry2.create("Assets/food_2.png");
	Smoke1.create("Assets/smoke_1.png");
	Smoke2.create("Assets/smoke_2.png");
	Fuck1.create("Assets/fuck_1.png");
	Fuck2.create("Assets/fuck_2.png");
}