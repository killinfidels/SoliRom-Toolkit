#pragma once
#include "Engine/Windows/Window.h"
#include "Engine/Log.h"

namespace SoliRom
{
	extern class AssetManager;
	extern class AssetViewer;
}

namespace SoliRom::Asset
{

	class Texture
	{
	private: //only public cus its being fucky, change later
		//stores info to create texture later
		Texture(std::string _name, std::string _path, bool _frame);
		//Text texture
		Texture(std::string _text, int _size, SDL_Color _color);
		//create texture

		//have to set rendering window if thats not done
		bool Load();

		//path of texture file
		std::string name;
		std::string path;
		std::string textureOrFrame;
		int fontSize;

		//Pointer to window to get renderer
		Window* window = NULL;
		SDL_Texture* texture = NULL;
		SDL_Color color;
		SDL_Rect size;

		bool loaded;
		bool frame;
		bool text;

	public:
		SDL_Texture* Get();
		Window* GetWindow();
		//Returns a rect with texture size and position at 0, 0
		SDL_Rect GetSize();
		~Texture();

		friend class ::SoliRom::AssetManager;
		friend class ::SoliRom::AssetViewer;
		friend class Animation;
	};
}

