#include "Knife.h"

Knife::Knife()
{
	a_knife = SoliRom::AssetManager::Get()->createAnimation("assets/KNIFE_1.png", 200);

	int sizeMul = 3;
	SetSize(30 * sizeMul, 78 * sizeMul);

	SetPos(SoliRom::App::Get()->GetCurrentWindow()->getWidth() - GetRect()->w, (int)(SoliRom::App::Get()->GetCurrentWindow()->getHeight() / 1.5) - (GetRect()->h / 2));
	//size 30 78
	a_knife->Start();
}

void Knife::animate()
{

	SetTexture(a_knife->Get());

}

bool Knife::knifeLogic(Guy* _weedguy)
{
	//IF KNIFE CLICKED
	if (SoliRom::Input::Click())
	{
		if (SoliRom::Input::MouseInRect(&screenRect))
		{
			held = true;
		}
	}

	if (held)
	{
		SetPos((SoliRom::Input::getMouse().x * (1 / cam->scale)) - (GetRect()->w / 2), (SoliRom::Input::getMouse().y * (1 / cam->scale)) - (GetRect()->h / 2));

		if (SoliRom::Input::getMouse().state != SoliRom::MouseState::HELD && !SoliRom::Input::Click())
		{
			held = false;
			SetPos(SoliRom::App::Get()->GetCurrentWindow()->getWidth() - GetRect()->w, (int)(SoliRom::App::Get()->GetCurrentWindow()->getHeight() / 1.5) - (GetRect()->h / 2));

			if (SoliRom::Input::MouseInRect(_weedguy->GetScreenRect()))
			{
				//kill the guy liksom
				SetPos(-1000, -1000);
				return true;
			}
		}
	}

	return false;
}
