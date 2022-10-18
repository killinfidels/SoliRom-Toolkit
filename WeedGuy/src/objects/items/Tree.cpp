#include "Tree.h"

Tree::Tree(int _tree, int _size, int _x, int _y)
{
	a_tree = SoliRom::AssetManager::Get()->createAnimation("assets/tree" + std::to_string(_tree) + "_1.png");

	a_tree->Start();

	if (a_tree->Get() != NULL)
	{
		load = true;

		int picW, picH;

		SDL_QueryTexture(a_tree->Get()->Get(), NULL, NULL, &picW, &picH);

		SetSize(_size, _size * (picH / (float)picW));
		SetPos(_x - GetRect()->w / 2, _y - GetRect()->h);
	}
}

void Tree::Animate()
{
	SetTexture(a_tree->Get());
}
