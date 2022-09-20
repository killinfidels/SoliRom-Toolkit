#pragma once
#include "../../core.h"
#include "../Object.h"}

class Chip : public Object
{
public:
	Chip();

	bool used = false;

	void animate();

	static int heldChip;

private:
	static SoliRom::Asset::Animation* a_chip;
};