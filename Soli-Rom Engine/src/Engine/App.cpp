#include "precompiledheaders.h"
#include "App.h"
#include "Log.h"

#ifdef _WIN32

#include <Windows.h>

void enableColors()
{
	DWORD consoleMode;
	HANDLE outputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	if (GetConsoleMode(outputHandle, &consoleMode))
	{
		SetConsoleMode(outputHandle, consoleMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
	}
}

#endif

namespace SoliRom
{
	App::App()
	{
		enableColors();

		if (SDL_Init(SDL_INIT_VIDEO) != 0)
		{
			SR_CORE_ERROR("SDL Init failed: %s", SDL_GetError());
		}
		else
		{
			SR_CORE_INFO("SDL Init Success.");
			//	Unecessary
			//if (IMG_Init())
			//{

			//}
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

	Window* App::getWindow()
	{
		return window;
	}

	App::~App()
	{
		SDL_Quit();
		IMG_Quit();
	}
}
