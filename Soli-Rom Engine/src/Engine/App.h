#pragma once
#include "precompiledheaders.h"
#include "Windows/Window.h"
#include "Windows/Layer.h"
#include "Engine/Tools/Timer.h"

namespace SoliRom
{
	class App
	{
	public:
		~App();

		//Create new Window
		Window* CreateWindow(std::string _name, int _width, int _height);
		Window* GetCurrentWindow();
		Window* GetWindow(std::string _name);
		void SetUpdateTick(int _millis);
		bool SetCurrentWindow(std::string _name);
		void DestroyWindow(std::string _name);
		bool AddLayer(Layer* _layer);
		void Quit();

		//Returns pointer to instance
		static App* Get();

	protected:
		App();

	private:
		//Layers - tempTest
		std::vector<Layer*> appLayers;

		//Windows
		std::vector<Window*> appWindows;
		int currentWindow = 0;

		//App run loop
		void Run();
		bool running = false;

		int FindWindow(std::string _name);

		//Instance of app
		static App* instance;

		bool usingUpdateTick = false;
		int updateTick = 0;
		Timer frameTimer;

		//set main function as friend so it can run app privates
		friend int ::main(int argc, char** argv);
	};

	//Creates app, defiend in Client
	App* CreateApp();
}