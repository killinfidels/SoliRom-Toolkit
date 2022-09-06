#include "Shack.h"

Shack* Shack::instance = 0;

SoliRom::App Game(scale);

Guy weedGuy;

Boof joint;

Knife knife;

things bagDorito; //makedoritobag class
SoliRom::Texture doritoBag;
chip chips[chipAmount];
bool usingChip[chipAmount];

things block;
SoliRom::Texture grass;

things blood;
SoliRom::Texture bloodsplat;
exhale smoke(&weedGuy);

Shack* Shack::getInstance()
{
	if (!instance)
	{
		instance = new Shack;
	}

	return instance;
}

Shack::Shack()
{
	scene = { "ext", "int" };
	currentScene = 0;

	//exterior
	exterior.create("Assets/shackExt.jpg");
	arrow.create("Assets/Arrow.png");

	right.setTexture(arrow);
	left.setTexture(arrow);

	screen.setSize(Game.getWindow()->getWindowWidth(), Game.getWindow()->getWindowHeight());
	right.setSize(128, 128);
	left.setSize(128, 128);
	door.setSize(187, 482);

	right.setPosition(Game.getWindow()->getWindowWidth() - right.getRect()->w, (Game.getWindow()->getWindowHeight() / 2) - (right.getRect()->h / 2));
	left.setPosition(0, right.getRect()->y);
	door.setPosition(405, 310);

	//interior
	interior.create("Assets/shackInt.jpg");
	arrowDown.create("Assets/ArrowDown.png");
	doritoBag.create("Assets/doritobag_1.png");
	grass.create("Assets/grass.png");
	bloodsplat.create("Assets/blood.png");

	back.setTexture(arrowDown);
	bagDorito.setTexture(doritoBag);
	chip::loadAssets();
	block.setTexture(grass);
	blood.setTexture(bloodsplat);

	back.setSize(128, 128);
	bagDorito.setSize(200, 200);
	block.setSize(300, 300);
	blood.setSize(200, 200);

	back.setPosition((Game.getWindow()->getWindowWidth() / 2) - (back.getRect()->w / 2), Game.getWindow()->getWindowHeight() - right.getRect()->h);
	bagDorito.setPosition(bagDorito.getRect()->w/10, (int)(Game.getWindow()->getWindowHeight() - bagDorito.getRect()->h));
	block.setPosition(weedGuy.getRect()->x + (weedGuy.getRect()->w / 2) - (block.getRect()->w / 2), weedGuy.getRect()->y + (weedGuy.getRect()->h) - (block.getRect()->h / 2) - 20);
	blood.setPosition(weedGuy.getRect()->x + (weedGuy.getRect()->w / 2) - (blood.getRect()->w / 2), weedGuy.getRect()->y + (weedGuy.getRect()->h / 2) - (blood.getRect()->h / 2));


	//rest
	screen.setTexture(exterior);
}

void Shack::Load()
{
	if (!loadSuccess)
	{
		if (scene[currentScene] == "int")
		{
			screen.setTexture(interior);

			physicsT.start();
		}

		if (scene[currentScene] == "ext")
		{
			screen.setTexture(exterior);
		}

		loadSuccess = true;
	}
}

void Shack::Script()
{
	SceneTransition();

	if (scene[currentScene] == "int" && loadSuccess)
	{
		//mouse click
		if (SoliRom::EventHandler::click())
		{
			//if bag click spawn dorito on bag
			bagDorito.reScale();
			if (SoliRom::EventHandler::mouseInObj(&bagDorito))
			{
				for (int i = 0; i < chipAmount; i++)
				{
					if (chips[i].used == false)
					{
						chips[i].setPosition((SoliRom::EventHandler::getMouseX() * (1 / scale)) - (chips[i].getRect()->w / 2), (SoliRom::EventHandler::getMouseY() * (1 / scale)) - (chips[i].getRect()->h / 2));
						chips[i].used = true;
						break;
						//chip::heldChip = i;
					}
				}
			}

			//click dorito to select
			for (int i = 0; i < chipAmount; i++)
			{
				chips[i].reScale();
				if (SoliRom::EventHandler::mouseInObj(&chips[i]))
				{
					chip::heldChip = i;
					break;
				}
			}

			//if idle switch animation to booger
			if (SoliRom::EventHandler::mouseInObj(&weedGuy) && weedGuy.currentAnimation == Guy::IDLE)
			{
				weedGuy.setAnimation(Guy::BOOGER, true, true);
			}
		}

		//mouse holding:
		if (SoliRom::EventHandler::getMouseState() == SoliRom::MouseCondition::HELD)
		{
			//if held on dorito follow mouse
			if (chip::heldChip != -1)
			{
				chips[chip::heldChip].setPosition((SoliRom::EventHandler::getMouseX() * (1/scale)) - (chips[chip::heldChip].getRect()->w / 2), (SoliRom::EventHandler::getMouseY() * (1 / scale)) - (chips[chip::heldChip].getRect()->h / 2));
			}
		}

		//mouse idle
		if (SoliRom::EventHandler::getMouseState() == SoliRom::MouseCondition::IDLE)
		{
			chip::heldChip = -1;
		}

		//hunger
		for (int i = 0; i < chipAmount; i++)
		{
			if (chips[i].getRect()->x > weedGuy.getRect()->x && chips[i].getRect()->x + (chips[i].getRect()->w / 2) < weedGuy.getRect()->x + weedGuy.getRect()->w)
			{
				if (chips[i].getRect()->y < weedGuy.getRect()->y + (weedGuy.getRect()->h / 3.5))
				{
					weedGuy.setAnimation(Guy::HUNGRY, true, false);
				}
				else if (chips[i].getRect()->y < weedGuy.getRect()->y + (weedGuy.getRect()->h / 2.5) && i != chip::heldChip)
				{
					chips[i].move(0, 1000);
				}
			}
			//set used chip when used
			if (chips[i].getRect()->y > Game.getWindow()->getWindowHeight() && i != chip::heldChip)
			{
				chips[i].used = false;
			}
		}

		//physics
		if (physicsT.check(1000/60))
		{
			physicsT.start();
			//dorito gravity
			for (int i = 0; i < chipAmount; i++)
			{
				if (i != chip::heldChip && chips[i].used == true)
				{
					chips[i].move(0, 7);
				}
			}

			//sends guy flying if you quit
			if (SoliRom::EventHandler::getQuit())
			{
				weedGuy.setAnimation(Guy::FUCK, true, true);

				if (weedGuy.getRect()->x > 300)
				{
					weedGuy.move((300 - weedGuy.getRect()->x)/10,0);
				}
				if (weedGuy.getRect()->y > 700)
				{
					weedGuy.move(0, (700 - weedGuy.getRect()->y) / 10);
				}
				blood.setPosition(weedGuy.getRect()->x + (weedGuy.getRect()->w / 2) - (blood.getRect()->w / 2), weedGuy.getRect()->y + (weedGuy.getRect()->h / 2) - (blood.getRect()->h / 2));
				//weedGuy.setSize(weedGuy.getRect()->w + 2, weedGuy.getRect()->h + 2);
			}
		}

		//you ghave to kill him !!!
		if (SoliRom::EventHandler::getQuit() && knife.knifeLogic(&weedGuy))
		{
			bloodT.start();
		}

		//weed stuff haha
		{
			if (joint.jointLogic(&weedGuy))
			{
				weedGuy.setAnimation(Guy::BOOF, true , true);
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

bool Shack::SceneTransition()
{
	//exterior scene
	if (scene[currentScene] == "ext")
	{
		//changes scene
		if (SoliRom::EventHandler::click())
		{
			if (SoliRom::EventHandler::mouseInObj(&door))
			{
				currentScene = 1;

				loadSuccess = false;
			}
		}
	}

	//interior scene
	if (scene[currentScene] == "int")
	{
		if (SoliRom::EventHandler::click())
		{
			if (SoliRom::EventHandler::mouseInObj(&back))
			{
				currentScene = 0;

				loadSuccess = false;
			}
		}
	}

	return !loadSuccess;
}

void Shack::Draw()
{
	SDL_RenderClear(Game.getWindow()->getRenderer());

	//exterior scene
	if (scene[currentScene] == "ext")
	{
		screen.draw();
		right.draw();
		left.draw(SDL_FLIP_HORIZONTAL);
		door.drawRect(true);
	}

	//interior scene
	if (scene[currentScene] == "int")
	{
		//background
		screen.draw();

		//things
		//block.draw();
		weedGuy.draw();

		if (!SoliRom::EventHandler::getQuit())
		{
			if (!smoke.done)
			{
				smoke.draw();
			}

			bagDorito.draw();
			joint.draw();


			for (int i = 0; i < chipAmount; i++)
			{
				chips[i].animate();
				chips[i].draw();
			}

			//hud
			back.draw();
			
		}
		else
		{
			if (!bloodT.check(1000))
			{
				blood.draw();
			}

			knife.draw();
		}

	}

	SDL_RenderPresent(Game.getWindow()->getRenderer());
}

bool Shack::SpecialQUIT()
{
	if (SoliRom::EventHandler::getQuit() && !bloodT.check(1000) && bloodT.check(200))
	{
		return true;
	}

	return false;
}