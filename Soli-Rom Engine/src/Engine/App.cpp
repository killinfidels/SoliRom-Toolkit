#include "precompiledheaders.h"
#include "Log.h"
#include "App.h"
#include "Input.h"

namespace SoliRom
{
	App::App()
	{
		//Initialize SDL_2
		if (SDL_Init(SDL_INIT_VIDEO) != 0)
		{
			SR_CORE_FATAL("SDL Init Failed: %s", SDL_GetError());
		}
		else
		{
			SR_CORE_INFO("SDL Init Success.");
			//	Unecessary BUT: Initialize SDL_img for .PNG and .JPG
			if (!(IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG)))
			{
				SR_CORE_FATAL("SDL_img Init Failed: %s", SDL_GetError());
			}
			else
			{
				SR_CORE_INFO("SDL_img Init Success.");
			}
		}
	}

	void App::Run()
	{
		bool running = true;

		while (running)
		{
			//call eventhandler, it stores all events in keyboardstate, mousestate and windowstate
			EventHandler::update();

			running = !EventHandler::getQuit();


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
		IMG_Quit();
	}

	Window* App::createWindow(std::string _name, int _width, int _height)
	{
		appWindow = Window(_name, _width, _height);

		return &appWindow;
	}
}
