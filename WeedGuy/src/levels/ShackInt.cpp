#include "ShackInt.h"

ShackInt* ShackInt::instance = NULL;

ShackInt* ShackInt::Get()
{
	if (!instance)
	{
		instance = new ShackInt;
	}

	return instance;
}

ShackInt::ShackInt() : smoke(&weedGuy)
{
	levelIdentification = LevelId::ShackInt;

	//interior
	interior = assetManager->createTexture("assets/shackInt.jpg");
	arrowDown = assetManager->createTexture("assets/ArrowDown.png");
	doritoBag = assetManager->createTexture("assets/doritobag_1.png");
	grass = assetManager->createTexture("assets/grass.png");
	bloodsplat = assetManager->createTexture("assets/blood.png");

	level.SetTexture(interior);
	back.SetTexture(arrowDown);
	bagDorito.SetTexture(doritoBag);
	block.SetTexture(grass);
	blood.SetTexture(bloodsplat);

	back.SetSize(128, 128);
	bagDorito.SetSize(200, 200);
	block.SetSize(300, 300);
	blood.SetSize(200, 200);
	level.SetSize(w_game->getWidth(), w_game->getHeight());

	back.SetPos((w_game->getWidth() / 2) - (back.GetRect()->w / 2), w_game->getHeight() - back.GetRect()->h);
	bagDorito.SetPos(bagDorito.GetRect()->w / 10, (int)(w_game->getHeight() - bagDorito.GetRect()->h));
	block.SetPos(weedGuy.GetRect()->x + (weedGuy.GetRect()->w / 2) - (block.GetRect()->w / 2), weedGuy.GetRect()->y + (weedGuy.GetRect()->h) - (block.GetRect()->h / 2) - 20);
	blood.SetPos(weedGuy.GetRect()->x + (weedGuy.GetRect()->w / 2) - (blood.GetRect()->w / 2), weedGuy.GetRect()->y + (weedGuy.GetRect()->h / 2) - (blood.GetRect()->h / 2));

}

void ShackInt::Load(LevelId _previousLevel)
{
	if (!loadSuccess)
	{
		physicsT.Reset();
		physicsT.Start();

		bloodT.Stop();
		bloodT.Reset();

		loadSuccess = true;
	}
}

void ShackInt::Script()
{
	if (loadSuccess)
	{
		physicsT.update();

		bloodT.update();

		//mouse Click
		if (SoliRom::Input::Click())
		{
			//if bag Click spawn dorito on bag
			if (SoliRom::Input::MouseInRect(bagDorito.GetScreenRect()))
			{
				for (int i = 0; i < ChipAmount; i++)
				{
					if (Chips[i].used == false)
					{
						Chips[i].SetPos(SoliRom::Input::getMouse().x + cam.x, SoliRom::Input::getMouse().y + cam.y);
						Chips[i].used = true;
						break;
						//Chip::heldChip = i;
					}
				}
			}

			//Click dorito to select
			for (int i = 0; i < ChipAmount; i++)
			{
				if (SoliRom::Input::MouseInRect(Chips[i].GetScreenRect()))
				{
					Chip::heldChip = i;
					break;
				}
			}

			//if idle switch animation to booger
			if (SoliRom::Input::MouseInRect(weedGuy.GetScreenRect()) && weedGuy.currentAnimation == Guy::IDLE)
			{
				weedGuy.setAnimation(Guy::BOOGER, true, true);
			}
		}

		//mouse holding:
		if (SoliRom::Input::Held())
		{
			//if held on dorito follow mouse
			if (Chip::heldChip != -1)
			{
				Chips[Chip::heldChip].SetPos(SoliRom::Input::getMouse().x + cam.x, SoliRom::Input::getMouse().y + cam.y);
			}
		}

		//mouse idle
		if (SoliRom::Input::getMouse().state == SoliRom::MouseState::IDLE)
		{
			Chip::heldChip = -1;
		}

		//hunger
		for (int i = 0; i < ChipAmount; i++)
		{
			if (Chips[i].GetRect()->x > weedGuy.GetRect()->x && Chips[i].GetRect()->x + (Chips[i].GetRect()->w / 2) < weedGuy.GetRect()->x + weedGuy.GetRect()->w)
			{
				if (Chips[i].GetRect()->y < weedGuy.GetRect()->y + (weedGuy.GetRect()->h / 3.5))
				{
					weedGuy.setAnimation(Guy::HUNGRY, true, false);
				}
				else if (Chips[i].GetRect()->y < weedGuy.GetRect()->y + (weedGuy.GetRect()->h / 2.5) && i != Chip::heldChip)
				{
					Chips[i].Move(0, 1000);
				}
			}
			//set used Chip when used
			if (Chips[i].GetRect()->y > w_game->getHeight() && i != Chip::heldChip)
			{
				Chips[i].used = false;
			}
		}

		//physics
		if (physicsT.checkElapsed(1000 / 60))
		{
			physicsT.Reset();
			//dorito gravity
			for (int i = 0; i < ChipAmount; i++)
			{
				if (i != Chip::heldChip && Chips[i].used == true)
				{
					Chips[i].Move(0, 7);
				}
			}

			//sends guy flying if you quit
			if (SoliRom::Input::getQuit())
			{
				weedGuy.setAnimation(Guy::FUCK, true, true);

				if (weedGuy.GetRect()->x > 300)
				{
					weedGuy.Move((300 - weedGuy.GetRect()->x) / 10, 0);
				}
				if (weedGuy.GetRect()->y > 700)
				{
					weedGuy.Move(0, (700 - weedGuy.GetRect()->y) / 10);
				}
				blood.SetPos(weedGuy.GetRect()->x + (weedGuy.GetRect()->w / 2) - (blood.GetRect()->w / 2), weedGuy.GetRect()->y + (weedGuy.GetRect()->h / 2) - (blood.GetRect()->h / 2));
				//weedGuy.SetSize(weedGuy.GetRect()->w + 2, weedGuy.GetRect()->h + 2);
			}
		}

		//you ghave to kill him !!!
		if (SoliRom::Input::getQuit() && knife.knifeLogic(&weedGuy))
		{
			bloodT.Start();
		}

		//weed stuff haha
		{
			if (joint.jointLogic(&weedGuy))
			{
				weedGuy.setAnimation(Guy::BOOF, true, true);
			}

			if (weedGuy.blowSmoke || !smoke.done)
			{
				weedGuy.blowSmoke = false;
				smoke.animate();
			}
		}


		weedGuy.animate();
		knife.animate();
	}
}

Level::LevelId ShackInt::LevelTransition()
{
	if (SoliRom::Input::Click())
	{
		if (SoliRom::Input::MouseInRect(back.GetScreenRect()))
		{
			loadSuccess = false;
			return LevelId::ShackExt;
		}
	}

	return LevelId::ShackInt;
}

void ShackInt::Draw()
{
	//background
	level.Draw();

	//Object
	block.Draw();
	weedGuy.Draw();

	if (!SoliRom::Input::getQuit())
	{
		if (!smoke.done)
		{
			smoke.Draw();
		}

		bagDorito.Draw();
		joint.Draw();


		for (int i = 0; i < ChipAmount; i++)
		{
			Chips[i].animate();
			Chips[i].Draw();
		}

		//hud
		back.Draw();

	}
	else
	{
		if (!bloodT.checkElapsed(1000))
		{
			blood.Draw();
		}

		knife.Draw();
	}

	SpecialQUIT();
}

bool ShackInt::SpecialQUIT()
{
	if (SoliRom::Input::getQuit() && !bloodT.checkElapsed(1000) && bloodT.checkElapsed(200))
	{
		app->Quit();
		return true;
	}

	return false;
}