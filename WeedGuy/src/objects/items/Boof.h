#pragma once
#include "../../core.h"
#include "../Object.h"}
#include "Guy.h"

class Boof : public Object
{
public:
	SoliRom::Asset::Texture* boof;

	Boof();

	bool held = false;

	bool jointLogic(Guy* _weedguy);

	int sk�kness = 90000;

};