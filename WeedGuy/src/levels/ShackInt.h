#pragma once
#include "../core.h"
#include "Level.h"
#include "../objects/Items.h"
#include "../objects/Object.h"

class ShackInt : public Level
{
	ShackInt();
	static ShackInt* instance;

public:
	static ShackInt* Get();
	~ShackInt();

	virtual void Load(LevelId _previousLevel) override;
	virtual void Script() override;
	virtual void Draw() override;
	//virtual void Quit() override;
	virtual LevelId LevelTransition() override;

	bool SpecialQUIT();

private:
	SoliRom::Timer physicsT;
	SoliRom::Timer bloodT;

	SoliRom::Asset::Texture* interior;
	SoliRom::Asset::Texture* arrowDown;
	SoliRom::Asset::Texture* bloodsplat;
	SoliRom::Asset::Texture* grass;
	SoliRom::Asset::Texture* doritoBag;

	Object level;
	Object left;
	Object right;
	Object back;

	Guy weedGuy;
	Boof joint;
	Knife knife;
	Object bagDorito; //makedoritobag class
	const static int ChipAmount = 20;
	Chip Chips[ChipAmount];
	bool usingChip[ChipAmount];
	Object block;
	Object blood;
	exhale smoke;
};
