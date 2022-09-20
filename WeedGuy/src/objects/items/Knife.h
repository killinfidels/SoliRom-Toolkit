#pragma once
#include "../../core.h"
#include "../Object.h"
#include "Guy.h"

class Knife : public Object
{
public:
	bool held = false;

	Knife();

	SoliRom::Asset::Animation* a_knife;

	void animate();

	bool knifeLogic(Guy* _weedguy);
};