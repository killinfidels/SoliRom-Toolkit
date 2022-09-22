#include "precompiledheaders.h"
#include "Engine/Windows/Window.h"
#include "Texture.h"
#include "Engine/Log.h"

namespace SoliRom::Asset
{
	Texture::Texture(std::string _name, std::string _path, bool _frame)
	{
		name = _name;
		path = _path;
		loaded = false;
		frame = _frame;

		textureOrFrame = "Texture";

		if (frame) //Says frame failed instead of texute if its part of an animation :p
			textureOrFrame = "Frame";

		SR_CORE_TRACE("%s '%s' created.", textureOrFrame.c_str(), name.c_str());
	}

	bool Texture::Load()
	{
		std::string textureOrFrame = "Texture";
		if (frame) //Says frame failed instead of texute if its part of an animation :p
			textureOrFrame = "Frame";

		if (window == NULL)
		{
			SR_CORE_WARN("%s '%' loading failed, no target window to render.\nPath: '%s'", textureOrFrame.c_str(), name.c_str(), path.c_str());
			return false;
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
}
