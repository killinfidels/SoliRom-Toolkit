#include <stdio.h>
#include <conio.h>
#include <chrono>
#include "TestSpace.h"

//textures

//dorito
SoliRom::Asset doritoBag;

//objects
guy weedGuy;
//dorito objects
SoliRom::GameObject bagDorito;
const int chipAmount = 20;
chip chips[chipAmount];
bool usingChip[chipAmount];

knife stabby;

int main(int argc, char* args[])
{
	if ((std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now().time_since_epoch()).count()) % 2 == 0)
		SR_INFO("gaylords unite");
	else
		SR_INFO("gaylords urinate");

	SR_INFO("press enter in console to toggle debug boxes");

	//Weedman textures


	//dorito textures
	doritoBag.createAsset(TestSpace.getWindow(), SoliRom::assetType::TEXTURE, "Assets/doritobag_1.png");
	chip::loadAssets();

	//dorito size position
	int bagMul = 2;
	bagDorito.setSize(100 * bagMul, 100 * bagMul);
	bagDorito.setPosition(TestSpace.getWindow()->getWindowWidth() / 20, (int)(TestSpace.getWindow()->getWindowHeight() / 1.5));

	const std::chrono::milliseconds frameTime(200);
	std::chrono::steady_clock::time_point t1;
	std::chrono::steady_clock::time_point t2;
	std::chrono::steady_clock::time_point bloodTime;
	std::chrono::steady_clock::time_point physics;
	const std::chrono::milliseconds physicsStep(10);
	t1 = std::chrono::steady_clock::now() - frameTime;
	physics = std::chrono::steady_clock::now();
	bloodTime = std::chrono::steady_clock::now() - std::chrono::milliseconds(100000);

	int frame = 1;

	bool once = false;

	bool skip = false;

	int yeet = 4;

	bool debugBox = false;

	guy::animation setAnimation = guy::IDLE;

	guy::animation lastAnimation = guy::IDLE;

	boof Jont;

	things block;
	block.setSize(300, 300);
	block.setPosition(weedGuy.getRect()->x + (weedGuy.getRect()->w / 2) - (block.getRect()->w / 2), weedGuy.getRect()->y + (weedGuy.getRect()->h) - (block.getRect()->h / 2) - 20);
	SoliRom::Asset grass;
	grass.createAsset(TestSpace.getWindow(), SoliRom::TEXTURE, "Assets/grass.png");
	block.setTexture(grass);

	things blood;
	blood.setSize(200, 200);
	blood.setPosition(weedGuy.getRect()->x + (weedGuy.getRect()->w / 2) - (blood.getRect()->w / 2), weedGuy.getRect()->y + (weedGuy.getRect()->h / 2) - (blood.getRect()->h / 2));
	SoliRom::Asset bloodsplat;
	bloodsplat.createAsset(TestSpace.getWindow(), SoliRom::TEXTURE, "Assets/blood.png");
	blood.setTexture(bloodsplat);
	exhale smoke(&weedGuy);

	while (!skip)
	{
		if (kbhit()) //temp exit no more now its object outlines
			if (getch() == '\r')
				debugBox = !debugBox;

		if (weedGuy.getRect()->x + weedGuy.getRect()->w < 0)
			skip = true;

		t2 = std::chrono::steady_clock::now(); //current time


		SoliRom::EventHandler::updateMouse();


		setAnimation = guy::IDLE;

		//CLICKING
		if (SoliRom::EventHandler::getMouseState() == SoliRom::MouseCondition::CLICKED)
		{
			//IF WEEDGUY CLICKED
			if (SoliRom::EventHandler::getMouseX() > weedGuy.getRect()->x && SoliRom::EventHandler::getMouseX() < weedGuy.getRect()->x + weedGuy.getRect()->w)
			{
				if (SoliRom::EventHandler::getMouseY() > weedGuy.getRect()->y && SoliRom::EventHandler::getMouseY() < weedGuy.getRect()->y + weedGuy.getRect()->h)
				{
					setAnimation = guy::BOOGER;
				}
			}

			//if bag click spawn dorito on bag
			if (SoliRom::EventHandler::getMouseX() > bagDorito.getRect()->x && SoliRom::EventHandler::getMouseX() < bagDorito.getRect()->x + bagDorito.getRect()->w)
			{
				if (SoliRom::EventHandler::getMouseY() > bagDorito.getRect()->y && SoliRom::EventHandler::getMouseY() < bagDorito.getRect()->y + bagDorito.getRect()->h)
				{
					for (int i = 0; i < chipAmount; i++)
					{
						if (chips[i].used == false)
						{
							chips[i].setPosition(SoliRom::EventHandler::getMouseX() - (chips[i].getRect()->w / 2), SoliRom::EventHandler::getMouseY() - (chips[i].getRect()->h / 2));
							chips[i].used = true;
							i = chipAmount;
						}
					}
				}
			}

			//click dorito to select
			for (int i = 0; i < chipAmount; i++)
			{
				if (SoliRom::EventHandler::getMouseX() > chips[i].getRect()->x && SoliRom::EventHandler::getMouseX() < chips[i].getRect()->x + chips[i].getRect()->w)
				{
					if (SoliRom::EventHandler::getMouseY() > chips[i].getRect()->y && SoliRom::EventHandler::getMouseY() < chips[i].getRect()->y + chips[i].getRect()->h)
					{
						chip::heldChip = i;
						i = chipAmount;
					}
				}
			}

		}

		if (Jont.jointLogic(&weedGuy))
		{
			setAnimation = guy::BOOF;
		}

		if (weedGuy.blowsmoke || !smoke.done)
		{
			weedGuy.blowsmoke = false;
			smoke.animate();
		}

		if (stabby.knifeLogic(&weedGuy))
		{
			bloodTime = std::chrono::steady_clock::now();
		}


		//foodguy
		for (int i = 0; i < chipAmount; i++)
		{
			if (chips[i].getRect()->x > weedGuy.getRect()->x && chips[i].getRect()->x + ( chips[i].getRect()->w / 2 )< weedGuy.getRect()->x + weedGuy.getRect()->w)
			{
				if (chips[i].getRect()->y < weedGuy.getRect()->y + (weedGuy.getRect()->h / 3.5))
				{
					setAnimation = guy::HUNGRY;
				}
				else if(lastAnimation == guy::HUNGRY && i != chip::heldChip)
				{
					chips[i].move(0, 1000);
				}
			}
			//set used chip when used
			if (chips[i].getRect()->y > TestSpace.getWindow()->getWindowHeight())
			{
				chips[i].used = false;
			}
		}

		//holding
		//if held on dorito follow mouse
		if (SoliRom::EventHandler::getMouseState() == SoliRom::MouseCondition::HELD)
		{
			if (chip::heldChip != -1)
			{
				chips[chip::heldChip].setPosition(SoliRom::EventHandler::getMouseX() - (chips[chip::heldChip].getRect()->w / 2), SoliRom::EventHandler::getMouseY() - (chips[chip::heldChip].getRect()->h / 2));
			}
		}

		if (SoliRom::EventHandler::getMouseState() == SoliRom::MouseCondition::IDLE)
		{
			chip::heldChip = -1;
		}

		//physics
		if (std::chrono::duration_cast<std::chrono::milliseconds>(t2.time_since_epoch() - physics.time_since_epoch()) > physicsStep)
		{
			//dorito gravity
			for (int i = 0; i < chipAmount; i++)
			{
				if (i != chip::heldChip && chips[i].used == true)
				{
					chips[i].move(0, 5);
				}
			}

				physics = std::chrono::steady_clock::now();

			if (SoliRom::EventHandler::getQuit())
			{
				weedGuy.setPosition(weedGuy.getRect()->x - yeet, weedGuy.getRect()->y - 2);
				weedGuy.setSize(weedGuy.getRect()->w + 2, weedGuy.getRect()->h + 2);
			}
		}

		//if quit fuck guy
		if (SoliRom::EventHandler::getQuit())
			setAnimation = guy::FUCK;

		weedGuy.animate(setAnimation);

		//clear
		SDL_RenderClear(TestSpace.getWindow()->getRenderer());

		block.draw();

		weedGuy.draw();

		if (!smoke.done)
		{
			smoke.draw();
		}

		if (std::chrono::duration_cast<std::chrono::milliseconds>(t2.time_since_epoch() - bloodTime.time_since_epoch()) < std::chrono::milliseconds(1000))
		{
			blood.draw();
		}

		stabby.animate();
		stabby.draw();


		Jont.draw();

		//render bag dorito
		SDL_RenderCopy(TestSpace.getWindow()->getRenderer(), doritoBag.getTexture(), NULL, bagDorito.getRect());


		//render chip
		for (int i = 0; i < chipAmount; i++)
		{
			chips[i].animate();
			chips[i].draw();
		}

		//render outlines
		if (debugBox)
		{
			//render color red
			SDL_SetRenderDrawColor(TestSpace.getWindow()->getRenderer(), 255, 0, 0, 255);
			//do boxes
			SDL_RenderDrawRect(TestSpace.getWindow()->getRenderer(), weedGuy.getRect());
			SDL_RenderDrawRect(TestSpace.getWindow()->getRenderer(), bagDorito.getRect());
			for (int i = 0; i < chipAmount; i++)
			{
				SDL_RenderDrawRect(TestSpace.getWindow()->getRenderer(), chips[i].getRect());
			}
			//render return to white
			SDL_SetRenderDrawColor(TestSpace.getWindow()->getRenderer(), 255, 255, 255, 255);
		}


		//render
		SDL_RenderPresent(TestSpace.getWindow()->getRenderer());

		//SR_INFO("FrameTime: ");

		lastAnimation = weedGuy.currentAnimation;
	}

	return 0;
}