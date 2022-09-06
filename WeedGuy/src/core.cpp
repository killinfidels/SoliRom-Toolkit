#include "core.h"

//SoliRom::App Game(scale);

SoliRom::Asset::Texture chip::chip1;
SoliRom::Asset::Texture chip::chip2;
SoliRom::Asset::Texture chip::chip3;

int chip::heldChip = -1;

Guy::Guy()
{
	sizeMul = 4;
	setSize(100 * sizeMul, 100 * sizeMul);
	setPosition(getWindow()->getWidth() - getRect()->w, (int)(getWindow()->getHeight() / 1.4) - (getRect()->h / 2));

	Idle1.create("Assets/idle_1.png", getWindow());
	Idle2.create("Assets/idle_2.png", getWindow());
	Idle3.create("Assets/idle_3.png", getWindow());
	Pick1.create("Assets/nosepick_1.png", getWindow());
	Pick2.create("Assets/nosepick_2.png", getWindow());
	Hungry1.create("Assets/food_1.png", getWindow());
	Hungry2.create("Assets/food_2.png", getWindow());
	Smoke1.create("Assets/smoke_1.png", getWindow());
	Smoke2.create("Assets/smoke_2.png", getWindow());
	Fuck1.create("Assets/fuck_1.png", getWindow());
	Fuck2.create("Assets/fuck_2.png", getWindow());
}

SoliRom::Window* getWindow()
{
	if (SoliRom::App::getCurrentWindow() == NULL)
	{
		SoliRom::App::createWindow("Virtual pet weed guy : )", 1280, 960);
	}

	return SoliRom::App::getCurrentWindow();
}