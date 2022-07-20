#include "precompiledheaders.h"
#include "App.h"

namespace SoliRom
{
	App::App()
	{
		if (SDL_Init(SDL_INIT_VIDEO) != 0)
		{
			SDL_Log("SDL Init failed: %s", SDL_GetError());
		}
		else
		{
			SDL_Log("SDL Init Success.");

		}

		window = new Window;
	}

	void App::Run()
	{
		bool running = true;

		while (running)
		{
			//call eventhandler, it stores all events in keyboardstate, mousestate and windowstate



			//if not minimized
				//update all layers
				
			//update windows/render


		}

		//close all layers
		//free all assets
	}

	App::~App()
	{
		SDL_Quit();
	}
}
