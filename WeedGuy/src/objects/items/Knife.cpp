#include "Knife.h"

Knife::Knife()
{
	a_knife = SoliRom::AssetManager::Get()->createAnimation("assets/KNIFE_1.png", 200);

	sizeMul = 3;
	setSize(30 * sizeMul, 78 * sizeMul);

	setPosition(SoliRom::App::Get()->getCurrentWindow()->getWidth() - GetRect()->w, (int)(SoliRom::App::Get()->getCurrentWindow()->getHeight() / 1.5) - (GetRect()->h / 2));
	//size 30 78
	a_knife->Start();
}

void Knife::animate()
{

	setTexture(a_knife->Get());

}

bool Knife::knifeLogic(Guy* _weedguy)
{
	//IF KNIFE CLICKED
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
			setPosition(SoliRom::App::Get()->getCurrentWindow()->getWidth() - GetRect()->w, (int)(SoliRom::App::Get()->getCurrentWindow()->getHeight() / 1.5) - (GetRect()->h / 2));

			if (SoliRom::EventHandler::mouseInObj(_weedguy))
			{
				//kill the guy liksom
				setPosition(-1000, -1000);
				return true;
			}
		}
	}

	return false;
}
