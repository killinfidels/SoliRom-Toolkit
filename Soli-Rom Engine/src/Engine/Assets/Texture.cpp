#include "precompiledheaders.h"
#include "Engine/Windows/Window.h"
#include "Texture.h"
#include "Engine/Log.h"

bool SoliRom::Asset::Texture::create(std::string _path, Window* _window)
{
	path = _path;
	window = _window;

	texture = IMG_LoadTexture(window->getSDL_Renderer(), path.c_str());
	if (texture == NULL)
	{
		SR_CORE_WARN("Texture failed to load: %s", path.c_str());
		return false;
	}

	return true;
}

SDL_Texture* SoliRom::Asset::Texture::get()
{
	return texture;
}
