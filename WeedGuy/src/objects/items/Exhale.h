#pragma once
#include "../../core.h"
#include "../Object.h"
#include "Guy.h"

class exhale : public Object
{
public:
	exhale(Guy* _weedGuy);

	SoliRom::Asset::Animation* a_exhale;

	bool done = true;

	bool animate();
};