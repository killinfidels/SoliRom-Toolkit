#pragma once

namespace SoliRom
{
	namespace Asset
	{
		class Texture
		{
		public:
			bool create(std::string _path);
			bool create(std::string _path, Window* _window);

			SDL_Texture* get();
		protected:

			SDL_Texture* texture;

			//path of texture file
			std::string path;
			//Pointer to window to get renderer
			Window* window;
		};
	}
}

