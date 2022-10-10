#include "Boof.h"

Boof::Boof()
{
	boof = SoliRom::AssetManager::Get()->createTexture("assets/jont.png");
	SetTexture(boof);
	setSize(450 / 2, 250 / 2);
}

bool Boof::jointLogic(Guy* _weedguy)
{
	//IF JOINT CLICKED

	if (SoliRom::EventHandler::click())
	{
		if (SoliRom::EventHandler::mouseInObj(this))
		{
			held = true;
		}
	}

	if (held)
	{
		setPosition((SoliRom::EventHandler::getMouse().x * (1 / scale)) - (GetRect()->w / 2), (SoliRom::EventHandler::getMouse().y * (1 / scale)) - (GetRect()->h / 2));

		if (SoliRom::EventHandler::getMouse().state != SoliRom::MouseState::HELD && !SoliRom::EventHandler::click())
		{
			held = false;
			setPosition(0, 0);

			if (SoliRom::EventHandler::mouseInObj(_weedguy))
			{
				//smoke joint
				return true;
			}
		}
	}


	return false;
}
