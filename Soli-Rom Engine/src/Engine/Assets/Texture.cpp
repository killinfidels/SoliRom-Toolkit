#include "precompiledheaders.h"
#include "Texture.h"

namespace SoliRom::Asset
{
	Texture::Texture(std::string _name, std::string _path, bool _frame)
	{
		name = _name;
		path = _path;
		loaded = false;
		frame = _frame;
		text = false;

		textureOrFrame = "Texture";

		if (frame) //Says frame failed instead of texute if its part of an animation :p
			textureOrFrame = "Frame";

		SR_CORE_TRACE("%s '%s' created.", textureOrFrame.c_str(), name.c_str());
	}

	Texture::Texture(std::string _text, int _size, SDL_Color _color)
	{
		name = _text;
		path = "NO PATH, TEXT TEXTURES";
		fontSize = _size;
		color = _color;
		loaded = false;
		frame = false;
		text = true;

		textureOrFrame = "Text";
		SR_CORE_TRACE("%s '%s' created.", textureOrFrame.c_str(), name.c_str());
	}


	bool Texture::Load()
	{
		if (window == NULL)
		{
			SR_CORE_WARN("%s '%' loading failed, no target window to render.\nPath: '%s'", textureOrFrame.c_str(), name.c_str(), path.c_str());
			return false;
		}
		else
		{
			if (text)
			{
				SDL_Surface* tempSurface = TTF_RenderText_Solid(TTF_OpenFont("assets/arial.ttf", fontSize), name.c_str(), color);
				texture = SDL_CreateTextureFromSurface(window->getSDL_Renderer(), tempSurface);
				SDL_FreeSurface(tempSurface);

				if (texture == NULL)
				{
					SR_CORE_WARN("%s failed to load: '%s'. Error: %s", textureOrFrame.c_str(), name.c_str(), SDL_GetError());
					return false;
				}
			}
			else
			{
				texture = IMG_LoadTexture(window->getSDL_Renderer(), path.c_str());
				if (texture == NULL)
				{
					SR_CORE_WARN("%s failed to load: '%s'. Error: %s\nPath: '%s'", textureOrFrame.c_str(), name.c_str(), SDL_GetError(), path.c_str());
					return false;
				}
			}
		}

		SR_CORE_TRACE("%s '%s' loaded for Window: '%s'.", textureOrFrame.c_str(), name.c_str(), window->getWindowName().c_str());
		
		loaded = true;
		return true;
	}

	Window* Texture::GetWindow()
	{
		return window;
	}

	SDL_Texture* Texture::Get()
	{
		return texture;
	}

	Texture::~Texture()
	{
		SDL_DestroyTexture(texture);
	}
}
