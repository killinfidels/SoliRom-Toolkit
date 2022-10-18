#include "Boof.h"

Boof::Boof()
{
	boof = SoliRom::AssetManager::Get()->createTexture("assets/jont.png");
	SetTexture(boof);
	SetSize(450 / 2, 250 / 2);
}

bool Boof::jointLogic(Guy* _weedguy)
{
	//IF JOINT CLICKED

	if (SoliRom::Input::Click())
	{
		if (SoliRom::Input::MouseInRect(GetScreenRect()))
		{
			held = true;
		}
	}

	if (held)
	{
		SetPos(SoliRom::Input::getMouse().x - GetRect()->w / 2, SoliRom::Input::getMouse().y - GetRect()->h / 2);

		if (SoliRom::Input::getMouse().state != SoliRom::MouseState::HELD && !SoliRom::Input::Click())
		{
			held = false;
			SetPos(0, 0);

			if (SoliRom::Input::MouseInRect(_weedguy->GetScreenRect()))
			{
				//smoke joint
				return true;
			}
		}
	}


	return false;
}
