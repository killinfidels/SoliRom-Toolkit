#include "Game.h"

void objectInit()
{
	bagDorito.setTexture(doritoBag);
	block.setSize(300, 300);
	block.setPosition(weedGuy.getRect()->x + (weedGuy.getRect()->w / 2) - (block.getRect()->w / 2), weedGuy.getRect()->y + (weedGuy.getRect()->h) - (block.getRect()->h / 2) - 20);
	grass.create("Assets/grass.png");
	block.setTexture(grass);
	blood.setSize(200, 200);
	blood.setPosition(weedGuy.getRect()->x + (weedGuy.getRect()->w / 2) - (blood.getRect()->w / 2), weedGuy.getRect()->y + (weedGuy.getRect()->h / 2) - (blood.getRect()->h / 2));
	bloodsplat.create("Assets/blood.png");
	blood.setTexture(bloodsplat);

	chip::loadAssets();

	bagDorito.setSize(200, 200);
}

int main(int argc, char* args[])
{
	if ((std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now().time_since_epoch()).count()) % 2 == 0)
		SR_INFO("gaylords unite");
	else
		SR_INFO("gaylords urinate");

	SR_INFO("press enter in console to toggle debug boxes");

	Shack* shackScene = Shack::getInstance();
	
	bool exit = false;
	bool debugBox = false;

	Timer frameT;

	printf("\x1B[?25l");

	while (!exit)
	{
		frameT.start();

		if (kbhit()) //temp exit no more now its object outlines
			if (getch() == '\r')
				debugBox = !debugBox;

		if (weedGuy.getRect()->x + weedGuy.getRect()->w < 0)
			exit = true;

		SoliRom::EventHandler::updateMouse();


		shackScene->Load();

		shackScene->Script();

		shackScene->Draw();
		
		exit = shackScene->SpecialQUIT();


		SR_TRACE("Frametime: %ims", frameT.difference());
		printf("\x1B[F");

	}

	return 0;
}