#pragma once
#include "precompiledheaders.h"
#include "Engine/Windows/Window.h"

namespace SoliRom
{

		class Texture
		{
		public:
			bool create(std::string _path);

			SDL_Texture* getTexture();
			static void setWindow(Window* _window);
		protected:

			SDL_Texture* texture;

			//path of texture file
			std::string path;
			//Pointer to window to get renderer
			static Window* window;
		};
}

