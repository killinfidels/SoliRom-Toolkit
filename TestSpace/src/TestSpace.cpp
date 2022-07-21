#include "TestSpace.h"
#include <stdio.h>
#include <conio.h>
#include <chrono>

SoliRom::App TestSpace;

SoliRom::Asset Idle1;
SoliRom::Asset Idle2;
SoliRom::Asset Idle3;

SoliRom::Asset Booger;

SoliRom::Asset Hungry1;
SoliRom::Asset Hungry2;

SoliRom::GameObject weedGuy;

int main(int argc, char* args[])
{
	printf("gaylords unite\n");
	printf("press enter in console to close\n");

	bool skip = false;


	Idle1.createAsset(TestSpace.getWindow(), SoliRom::assetType::TEXTURE, "Assets/idle_1.png");
	Idle2.createAsset(TestSpace.getWindow(), SoliRom::assetType::TEXTURE, "Assets/idle_2.png");
	Idle3.createAsset(TestSpace.getWindow(), SoliRom::assetType::TEXTURE, "Assets/idle_3.png");

	Booger.createAsset(TestSpace.getWindow(), SoliRom::assetType::TEXTURE, "nosepick.png");
	printf("%s", IMG_GetError());

	Hungry1.createAsset(TestSpace.getWindow(), SoliRom::assetType::TEXTURE, "Assets/food_1.png");
	Hungry2.createAsset(TestSpace.getWindow(), SoliRom::assetType::TEXTURE, "Assets/food_2.png");

	int weedMultiplier = 2;

	weedGuy.setSize(200*weedMultiplier, 200*weedMultiplier);
	
	weedGuy.setPosition(0, 0);
	weedGuy.setPosition((TestSpace.getWindow()->getWindowWidth() / 2) - (weedGuy.getRect()->w / 2), (TestSpace.getWindow()->getWindowHeight() / 2) - (weedGuy.getRect()->h / 2));

	//SDL_Rect* fuck = weedGuy.getRect();
	SDL_RenderClear(TestSpace.getWindow()->getRenderer());
	SDL_RenderCopy(TestSpace.getWindow()->getRenderer(), Booger.getTexture(), NULL, weedGuy.getRect());
	SDL_RenderPresent(TestSpace.getWindow()->getRenderer());
	printf("%s", SDL_GetError());

	const std::chrono::milliseconds frameTime(200);
	std::chrono::steady_clock::time_point t1;
	std::chrono::steady_clock::time_point t2;
	t1 = std::chrono::steady_clock::now() - frameTime;

	int frame = 1;

	SDL_Texture* currentFrame = Idle1.getTexture();
	while (!skip)
	{
		if (kbhit())
			if (getch() == '\r')
				skip = true;
		t2 = std::chrono::steady_clock::now();

		if (std::chrono::duration_cast<std::chrono::milliseconds>(t2.time_since_epoch() - t1.time_since_epoch()) > frameTime)
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

		SDL_RenderClear(TestSpace.getWindow()->getRenderer());
		SDL_RenderCopy(TestSpace.getWindow()->getRenderer(), currentFrame, NULL, weedGuy.getRect());
		SDL_RenderPresent(TestSpace.getWindow()->getRenderer());
	}

	return 0;
}