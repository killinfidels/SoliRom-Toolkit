#pragma once
#include "Engine/Log.h"
#include "Engine/Windows/Window.h"
#include "Engine/Assets/Texture.h"
#include "Engine/Assets/Animation.h"
#include "Engine/Assets/Sound.h"
#include "Engine/App.h"

namespace SoliRom
{
	class AssetManager
	{
	private:
		AssetManager();
		static AssetManager* instance;

	public:
		~AssetManager();
		//Get AssetManager instance
		static AssetManager* Get();

		//filename will be used as name
		Asset::Texture* createTexture(std::string _path);
		Asset::Texture* createTexture(std::string _name, std::string _path);
		Asset::Animation* createAnimation(std::string _path, int _frameTime);
		Asset::Animation* createAnimation(std::string _name, std::string _path, int _frameTime);
		Asset::Animation* createAnimation(std::string _path);
		Asset::Animation* createAnimation(std::string _name, std::string _path);
		Asset::Animation* createAnimationFromFile(std::string _name, std::string _path);
		Asset::Animation* createAnimationFromFile(std::string _path);
		Asset::Sound* createSound();

		Asset::Texture* getTexture(std::string _name);
		Asset::Animation* getAnimation(std::string _name);
		Asset::Sound* getSound(std::string _name);

		void setWindow(Window* _window);

	private:
		std::vector<Asset::Texture*> textures;
		std::vector<Asset::Animation*> animations;
		std::vector<Asset::Sound*> sounds;

		bool noWindowLoad = true;

		Window* defaultWindow;
	};

}
