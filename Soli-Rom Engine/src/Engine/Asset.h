#pragma once

namespace SoliRom
{

	enum assetType
	{
		TEXTURE,
		ANIMATION,
		SOUND,
		TEXT,
		ENDOFLIST
	};

	class Asset
	{
		bool createAsset(Window* window, assetType type, std::string path);

		//bool createAsset(assetType type, std::string path);

	

		assetType type = ENDOFLIST;

		std::string name = "defaultName";

		std::string path = "";

		SDL_Texture* getTexture();

		int animationFrames = 1;
		std::vector<SDL_Texture*> texture;
		std::vector<int> frametimes;
		//somes shit for sound
		//some shit for text
	};
}

