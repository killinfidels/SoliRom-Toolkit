#pragma once
#include "precompiledheaders.h"
#include "Windows/Window.h"
#include "Windows/Layer.h"

namespace SoliRom
{
	class App
	{
	public:
		~App();

		//Create new Window
		Window* createWindow(std::string _name, int _width, int _height);
		Window* getCurrentWindow();
		Window* getCurrentWindow(std::string _name);
		bool setCurrentWindow(std::string _name);
		bool addLayer(Layer* _layer);

		//Returns pointer to instance
		static App* Get();

	protected:
		App();

	public:
		//Layers - tempTest
		std::vector<Layer*> appLayers;

		//Windows
		std::vector<Window*> appWindows;
		int currentWindow = 0;

		//App run loop
		void Run();

		//Instance of app
		static App* instance;

		//set main function as friend so it can run app privates
		friend int ::main(int argc, char** argv);
	};

	//Creates app, defiend in Client
	App* CreateApp();
}