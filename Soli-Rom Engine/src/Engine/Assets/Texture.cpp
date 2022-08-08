#include "precompiledheaders.h"
#include "Texture.h"
#include "../Log.h"

namespace SoliRom
{
	Window* Texture::window = NULL;

	bool Texture::create(std::string _path)
	{
		path = _path;
		texture = IMG_LoadTexture(window->getRenderer(), path.c_str());
		if (texture == NULL)
		{
			SR_CORE_WARN("Texture failed to load: %s", path.c_str());
		}
		return false;
	}

	SDL_Texture* Texture::getTexture()
	{
		return texture;
	}

	void Texture::setWindow(Window* _window)
	{
		window = _window;
	}
}
