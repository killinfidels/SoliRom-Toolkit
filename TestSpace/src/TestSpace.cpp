#include <stdio.h>
#include <conio.h>
#include <chrono>
#include "TestSpace.h"

//textures
//weedguy idle
SoliRom::Asset Idle1;
SoliRom::Asset Idle2;
SoliRom::Asset Idle3;
//weedguy booger
SoliRom::Asset Booger;
//weedguy wants dorito
SoliRom::Asset Hungry1;
SoliRom::Asset Hungry2;
//dorito
SoliRom::Asset doritoBag;

//objects
SoliRom::GameObject weedGuy;
//dorito objects
SoliRom::GameObject bagDorito;
const int chipAmount = 20;
chip chips[chipAmount];
bool usingChip[chipAmount];


int main(int argc, char* args[])
{
	if ((std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now().time_since_epoch()).count()) % 2 == 0)
		SR_INFO("gaylords unite");
	else
		SR_INFO("gaylords urinate");

	SR_INFO("press enter in console to toggle debug boxes");

	//Weedman textures
	Idle1.createAsset(TestSpace.getWindow(), SoliRom::assetType::TEXTURE, "../Assets/idle_1.png");
	Idle2.createAsset(TestSpace.getWindow(), SoliRom::assetType::TEXTURE, "../Assets/idle_2.png");
	Idle3.createAsset(TestSpace.getWindow(), SoliRom::assetType::TEXTURE, "../Assets/idle_3.png");
	Booger.createAsset(TestSpace.getWindow(), SoliRom::assetType::TEXTURE, "../Assets/nosepick_1.png");
	Hungry1.createAsset(TestSpace.getWindow(), SoliRom::assetType::TEXTURE, "../Assets/food_1.png");
	Hungry2.createAsset(TestSpace.getWindow(), SoliRom::assetType::TEXTURE, "../Assets/food_2.png");

	//dorito textures
	doritoBag.createAsset(TestSpace.getWindow(), SoliRom::assetType::TEXTURE, "../Assets/doritobag_1.png");
	chip::loadAssets();
	//weedman size position
	int weedMul = 4; //size mult
	weedGuy.setSize(100 * weedMul, 100 * weedMul);
	
	weedGuy.setPosition((int)(TestSpace.getWindow()->getWindowWidth() / 1.3) - (weedGuy.getRect()->w / 2), (int)(TestSpace.getWindow()->getWindowHeight() / 1.5) - (weedGuy.getRect()->h / 2));

	//dorito size position
	int bagMul = 2;
	bagDorito.setSize(100 * bagMul, 100 * bagMul);
	bagDorito.setPosition(TestSpace.getWindow()->getWindowWidth() / 5, (int)(TestSpace.getWindow()->getWindowHeight() / 1.5));

	const std::chrono::milliseconds frameTime(200);
	std::chrono::steady_clock::time_point t1;
	std::chrono::steady_clock::time_point t2;
	std::chrono::steady_clock::time_point physics;
	const std::chrono::milliseconds physicsStep(10);
	t1 = std::chrono::steady_clock::now() - frameTime;
	physics = std::chrono::steady_clock::now();

	int frame = 1;

	bool once = false;

	SDL_Texture* currentFrame = Idle1.getTexture();
	bool skip = false;

	int yeet = 25;

	bool debugBox = false;

	while (!skip)
	{
		if (kbhit()) //temp exit no more now its object outlines
			if (getch() == '\r')
				debugBox = !debugBox;

		if (weedGuy.getRect()->y + weedGuy.getRect()->h < 0)
			skip = true;

		t2 = std::chrono::steady_clock::now(); //current time

		//weedguy idle animation
		if (std::chrono::duration_cast<std::chrono::milliseconds>(t2.time_since_epoch() - t1.time_since_epoch()) > frameTime) //crazy animation system
		{
			switch (frame)
			{
			case 1:
				currentFrame = Idle1.getTexture();
				break;
			case 2:
				currentFrame = Idle2.getTexture();
				break;
			case 3:
				currentFrame = Idle3.getTexture();
				frame = 0;
				break;
			default:
				break;
			}

			t1 = std::chrono::steady_clock::now();

			frame++;
		}

		SoliRom::EventHandler::updateMouse();

		//CLICKING
		if (SoliRom::EventHandler::getMouseState() == SoliRom::MouseCondition::CLICKED)
		{
			//IF WEEDGUY CLICKED
			if (SoliRom::EventHandler::getMouseX() > weedGuy.getRect()->x && SoliRom::EventHandler::getMouseX() < weedGuy.getRect()->x + weedGuy.getRect()->w)
			{
				if (SoliRom::EventHandler::getMouseY() > weedGuy.getRect()->y && SoliRom::EventHandler::getMouseY() < weedGuy.getRect()->y + weedGuy.getRect()->h)
				{
					currentFrame = Booger.getTexture(); //SET BOOGER
					t1 = std::chrono::steady_clock::now() + std::chrono::milliseconds(500);
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

		for (int i = 0; i < chipAmount; i++)
		{
			if (chips[i].getRect()->x > weedGuy.getRect()->x && chips[i].getRect()->x + ( chips[i].getRect()->w / 2 )< weedGuy.getRect()->x + weedGuy.getRect()->w)
			{
				if (chips[i].getRect()->y < weedGuy.getRect()->y + (weedGuy.getRect()->h / 2))
				{
					currentFrame = Hungry2.getTexture(); //SET hunger
				}
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
					chips[i].move(0, 1);
				}
			}

			if (SoliRom::EventHandler::getQuit())
			{
				physics = std::chrono::steady_clock::now();
				weedGuy.setPosition(weedGuy.getRect()->x, weedGuy.getRect()->y - yeet);
			}
		}

		//clear
		SDL_RenderClear(TestSpace.getWindow()->getRenderer());

		//if quit flip guy
		if (SoliRom::EventHandler::getQuit())
			SDL_RenderCopyEx(TestSpace.getWindow()->getRenderer(), currentFrame, NULL, weedGuy.getRect(), 0, NULL, SDL_FLIP_VERTICAL);
		else //render guy
			SDL_RenderCopy(TestSpace.getWindow()->getRenderer(), currentFrame, NULL, weedGuy.getRect());

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
	}

	return 0;
}