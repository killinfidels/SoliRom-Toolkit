#include "precompiledheaders.h"
#include "../Windows/Window.h"
#include "Asset.h"
#include "../Log.h"

namespace SoliRom
{
	Asset::Asset()
	{
		tempTexture = NULL;
	}

	bool Asset::createAsset(Window* window, assetType type, std::string _path)
	{
		path = _path;
		switch (type)
		{
		case SoliRom::TEXTURE:
			tempTexture = IMG_LoadTexture(window->getRenderer(), path.c_str());
			if (tempTexture  == NULL)
			{
				SR_CORE_WARN("Texture failed to load: %s", path.c_str());
			}
			break;
		case SoliRom::ANIMATION:
			break;
		case SoliRom::SOUND:
			break;
		case SoliRom::TEXT:
			break;
		case SoliRom::ENDOFLIST:
			break;
		default:
			break;
		}
		return false;
	}
	SDL_Texture* Asset::getTexture()
	{
		return tempTexture;
	}
}
