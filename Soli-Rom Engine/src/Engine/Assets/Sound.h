#pragma once

namespace SoliRom
{
	class AssetManager;
	class AssetViewer;
}

namespace SoliRom::Asset
{
	class Sound
	{

		std::string name, path;

		friend class ::SoliRom::AssetManager;
		friend class ::SoliRom::AssetViewer;
	};
}

