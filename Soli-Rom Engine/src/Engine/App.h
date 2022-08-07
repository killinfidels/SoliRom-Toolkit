#pragma once
#include "precompiledheaders.h"
#include "Windows/Window.h"

namespace SoliRom
{
	class App
	{
	public:
		App();
		~App();

		//Create new Window
		Window* createWindow(std::string _name, int _width, int _height);

	private:
		Window* getCurrentWindow();

		Window appWindow;

		//Creates app, defiend in Client
		static App* CreateApp();

		//App run loop
		void Run();

		//Instance of app
		static App* app_;

		//set main function as friend so it can run app privates
		friend int ::main(int argc, char** argv);
	};
}