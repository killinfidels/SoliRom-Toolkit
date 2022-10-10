#include "precompiledheaders.h"
#include "Log.h"
#include "Input.h"
#include "Assets/AssetManager.h"
#include "Assets/AssetViewer.h"
#include "App.h"

namespace SoliRom
{
	App* App::instance = nullptr;

	bool App::AddLayer(Layer* _layer)
	{
		appLayers.push_back(_layer);
		return false;
	}

	void App::Quit()
	{
		running = false;
	}

	App* App::Get()
	{
		return instance;
	}

	App::App()
	{
		if (instance != nullptr)
		{
			SR_CORE_ERROR("Application already exists!");
		}
		else
		{
			instance = this;

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
					SR_CORE_FATAL("SDL_img Init Failed: %s", IMG_GetError());
				}
				else
				{
					SR_CORE_INFO("SDL_img Init Success.");
					if (TTF_Init() == -1)
					{
						SR_CORE_FATAL("SDL_ttf Init Failed: %s", TTF_GetError());
					}
					else
					{
						SR_CORE_INFO("SDL_ttf Init Success.");
						running = true;
					}
				}
			}
		}
	}

	void App::Run()
	{
		AddLayer(new AssetViewer());

		frameTimer.Start();
		while (running)
		{
			frameTimer.update();

			if (!usingUpdateTick || frameTimer.checkElapsed(updateTick))
			{
				frameTimer.Reset();

				//call eventhandler, it stores all events in keyboardstate, mousestate and windowstate
				EventHandler::update();

				//if not minimized
					//update all layers
					//LAYERS IS HOW U MAKE GAME
					//update windows/render
				for (int i = 0; i < appWindows.size(); i++)
					SDL_RenderClear(appWindows[i]->getSDL_Renderer());

				for (int i = 0; i < appLayers.size(); i++)
				{
					appLayers[i]->OnEvent();
					appLayers[i]->OnUpdate();
				}

				for (int i = 0; i < appWindows.size(); i++)
					SDL_RenderPresent(appWindows[i]->getSDL_Renderer());
			}
		}

		//close all layers
		//free all assets
	}

	int App::FindWindow(std::string _name)
	{
		for (int i = 0; i < appWindows.size(); i++)
		{
			if (appWindows[i]->getWindowName() == _name)
			{
				return i;
			}
		}

		SR_CORE_WARN("NO WINDOW WITH NAME: '%s'!!", _name);

		return -1;
	}

	App::~App()
	{
		for (int i = 0; i < appWindows.size(); i++)
			appWindows[i]->~Window();

		SDL_Quit();
		IMG_Quit();
	}

	Window* App::CreateWindow(std::string _name, int _width, int _height)
	{
		bool change = false;
		int nameNr = 1;
		std::string updatedName = _name;
		//instance->currentWindow = 1;
		//identical names fix: name, name_2, name_3
		for (int i = 0; i < instance->appWindows.size(); i++)
		{
			if (instance->appWindows[i]->getWindowName() == updatedName)
			{
				i = 0;
				change = true;
				nameNr++;
				updatedName = _name + "_" + std::to_string(nameNr);
			}
		}

		//on name change!
		if (change)
		{
			SR_CORE_WARN("Window name changed to: %s", updatedName);
		}

		//add window to array
		instance->appWindows.push_back(new Window(updatedName, _width, _height));

		return instance->appWindows.back();
	}

	Window* App::GetCurrentWindow()
	{
		if (appWindows.size() != 0)
		{
			return appWindows[currentWindow];
		}

		SR_CORE_FATAL("COULD NOT GET CURRENT WINDOW, NO WINDOWS!!");

		return NULL;
	}

	Window* App::GetWindow(std::string _name)
	{
		int tempNr = FindWindow(_name);

		if (tempNr != -1)
			return appWindows[tempNr];

		SR_CORE_FATAL("COULD NOT GET WINDOW: '%s'!!", _name);

		return NULL;
	}

	void App::SetUpdateTick(int _millis)
	{
		if (!usingUpdateTick)
			usingUpdateTick = !usingUpdateTick;

		updateTick = _millis;
	}

	bool App::SetCurrentWindow(std::string _name)
	{
		int tempNr = FindWindow(_name);

		if (tempNr != -1)
		{
			currentWindow = tempNr;
			return true;
		}

		SR_CORE_ERROR("COULD NOT SET CURRENT WINDOW: '%s'!!", _name);

		return false;
	}

	void App::DestroyWindow(std::string _name)
	{
		int tempNr = FindWindow(_name);

		if (tempNr != -1)
		{
			delete appWindows[tempNr];
			appWindows.erase(appWindows.begin() + tempNr);
		}
		else
		{
			SR_CORE_ERROR("COULD NOT DESTROY WINDOW: '%s'!!", _name);
		}
	}
}
