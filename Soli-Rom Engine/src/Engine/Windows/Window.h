#pragma once
#include "precompiledheaders.h"

namespace SoliRom
{
	class Window
	{
	public:
		~Window();
		
		SDL_Renderer* getSDL_Renderer();

		SDL_Window* getSDL_Window();
		
		int getWidth();
		int getHeight();
		std::string getWindowName();

	private:
		friend class App;
		//temp so it works

		//Called from app.createwindow
		Window(std::string _name, int _width, int _height);


		std::string name = "NO WINDOW";
		SDL_Window* window = NULL;
		SDL_Surface* screensurface = NULL;
		SDL_Renderer* renderer = NULL;

		int width, height;
	};
}
