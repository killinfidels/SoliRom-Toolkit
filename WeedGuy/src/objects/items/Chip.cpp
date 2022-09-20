#include "Chip.h"

int Chip::heldChip = -1;
SoliRom::Asset::Animation* Chip::a_chip = NULL;

Chip::Chip()
{
	sizeMul = 1;
	setSize(100 * sizeMul, 100 * sizeMul);
	setPosition(-10000, -10000); //off screen so its invis

	a_chip = SoliRom::AssetManager::Get()->createAnimation("assets/chip_1.png", 200);
	a_chip->Start();
}

void Chip::animate()
{
	setTexture(a_chip->Get());
}
