#include "Chip.h"

int Chip::heldChip = -1;
SoliRom::Asset::Animation* Chip::a_chip = NULL;

Chip::Chip()
{
	int sizeMul = 1;
	SetSize(100 * sizeMul, 100 * sizeMul);
	SetPos(-10000, -10000); //off screen so its invis
	SetOffset(-GetRect()->w / 2, -GetRect()->h / 2);

	a_chip = SoliRom::AssetManager::Get()->createAnimation("assets/chip_1.png", 200);
	a_chip->Start();
}

void Chip::animate()
{
	SetTexture(a_chip->Get());
}
