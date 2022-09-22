#pragma once
#include "Engine/Windows/Window.h"
#include "Engine/Log.h"

namespace SoliRom
{
	class AssetManager;
}

namespace SoliRom::Asset
{

	class Texture
	{
	private: //only public cus its being fucky, change later
		//stores info to create texture later
		Texture(std::string _name, std::string _path, bool _frame);
		//create texture

	private:

		//have to set rendering window if thats not done
		bool Load();

		//path of texture file
		std::string name;
		std::string path;
		std::string textureOrFrame;

		//Pointer to window to get renderer
		Window* window = NULL;
		SDL_Texture* texture = NULL;

		bool loaded;
		bool frame;

	public:
		SDL_Texture* Get();
		Window* GetWindow();

		~Texture();

		friend class ::SoliRom::AssetManager;
		friend class Animation;
	};
}

