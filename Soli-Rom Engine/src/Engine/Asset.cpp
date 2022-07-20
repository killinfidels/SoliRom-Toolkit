#include "precompiledheaders.h"
#include "Window.h"
#include "Asset.h"

namespace SoliRom
{
	bool Asset::createAsset(Window* window, assetType type, std::string path)
	{
		switch (type)
		{
		case SoliRom::TEXTURE:
			IMG_LoadTexture(window->getRenderer(), path.c_str());
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
}
