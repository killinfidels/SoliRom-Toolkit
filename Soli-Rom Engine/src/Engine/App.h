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
		static Window* createWindow(std::string _name, int _width, int _height);
		Window* getCurrentWindow();
		Window* getCurrentWindow(std::string _name);
		bool setCurrentWindow(std::string _name);
		bool addLayer(Layer* _layer);

		static App& getInstance();

	protected:
		App();

	public:
		//Layers - tempTest
		std::vector<Layer*> appLayers;

		//Windows
		std::vector<Window*> appWindows;
		int currentWindow = 0;

		//Creates app, defiend in Client
		static App* CreateApp();

		//App run loop
		void Run();

		//Instance of app
		static App* instance;

		//set main function as friend so it can run app privates
		friend int ::main(int argc, char** argv);
	};
}