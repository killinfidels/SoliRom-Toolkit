#pragma once
#include "core.h"
#include "Zone.h"
#include "timer.h"

class Shack : public Zone
{
public:
	static Shack* getInstance();
	~Shack()
	{

	}

	void Load();

	void Script();

	bool SceneTransition();

	void Draw();

	bool SpecialQUIT();

private:
	Timer physicsT;
	Timer bloodT;
	Shack();
	static Shack* instance;

	SoliRom::Asset::Texture exterior;
	SoliRom::Asset::Texture interior;

	SoliRom::Asset::Texture arrow;
	SoliRom::Asset::Texture arrowDown;

	things screen;

	things door;
	things left;
	things right;
	things back;

	SoliRom::Window* w_game;

};
extern Guy weedGuy;
extern Boof joint;
extern Knife knife;
extern things bagDorito; //makedoritobag class
extern SoliRom::Asset::Texture doritoBag;
const int chipAmount = 20;
extern chip chips[chipAmount];
extern bool usingChip[chipAmount];
extern things block;
extern SoliRom::Asset::Texture grass;
//block.setSize(300, 300);
//block.setPosition(weedGuy.getRect()->x + (weedGuy.getRect()->w / 2) - (block.getRect()->w / 2), weedGuy.getRect()->y + (weedGuy.getRect()->h) - (block.getRect()->h / 2) - 20);
//grass.create("Assets/grass.png");
//block.setTexture(grass);
//blood.setSize(200, 200);
//blood.setPosition(weedGuy.getRect()->x + (weedGuy.getRect()->w / 2) - (blood.getRect()->w / 2), weedGuy.getRect()->y + (weedGuy.getRect()->h / 2) - (blood.getRect()->h / 2));
//bloodsplat.create("Assets/blood.png");
//blood.setTexture(bloodsplat);
extern things blood;
extern SoliRom::Asset::Texture bloodsplat;
extern exhale smoke;