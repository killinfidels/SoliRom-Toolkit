#include "precompiledheaders.h"
#include "Engine/Log.h"
#include "Engine/Windows/Window.h"
#include "Engine/Assets/Texture.h"
#include "Engine/Assets/Animation.h"
#include "Engine/Assets/Sound.h"
#include "AssetManager.h"
#include "Engine/App.h"

namespace SoliRom
{
	AssetManager* AssetManager::instance = NULL;

	AssetManager::AssetManager()
	{
		defaultWindow = NULL;

		if (instance != NULL)
		{
			SR_CORE_ERROR("Assetmanager already exists!");
		}
		else
		{
			defaultWindow = App::Get()->getCurrentWindow();

			if (defaultWindow == NULL)
			{
				//if no default window then ill wait for loading until its created
				noWindowLoad = false;
			}

			instance = this;

			//load fgiles
			//like files that have been loaded before
		}

	}

	AssetManager* AssetManager::Get()
	{
		if (instance == NULL)
		{
			new AssetManager;
		}

		return instance;
	}

	Asset::Texture* AssetManager::createTexture(std::string _path)
	{
		//creates name from path
		std::string name = _path.substr(_path.rfind("/") + 1, _path.rfind(".") - _path.rfind("/") - 1);
		return createTexture(name, _path);
	}

	Asset::Texture* AssetManager::createTexture(std::string _name, std::string _path)
	{
		textures.push_back(new Asset::Texture(_name, _path, false));
		//textures.emplace_back(_path, _name, defaultWindow, false);
		if (defaultWindow != nullptr)
		{
			textures.back()->window = defaultWindow;
			textures.back()->Load();
		}
		return textures.back();
	}

	Asset::Animation* AssetManager::createAnimation(std::string _path, int _frameTime)
	{
		std::string name = _path.substr(_path.rfind("/") + 1, _path.rfind("_") - _path.rfind("/") - 1);
		return createAnimation(name, _path, _frameTime);
	}

	Asset::Animation* AssetManager::createAnimation(std::string _name, std::string _path, int _frameTime)
	{
		animations.push_back(new Asset::Animation(_name, _path, _frameTime));
		//animations.emplace_back(_path, _frameTime, defaultWindow);
		if (defaultWindow != nullptr)
		{
			animations.back()->window = defaultWindow;
			animations.back()->Load();
		}
		return animations.back();
	}

	Asset::Animation* AssetManager::createAnimation(std::string _path)
	{
		std::string name = _path.substr(_path.rfind("/") + 1, _path.rfind("_") - _path.rfind("/") - 1);
		return createAnimation(name, _path);
	}

	Asset::Animation* AssetManager::createAnimation(std::string _name, std::string _path)
	{
		animations.push_back(new Asset::Animation(_name, _path));
		//animations.emplace_back(_path, _frameTime, defaultWindow);
		if (defaultWindow != nullptr)
		{
			animations.back()->window = defaultWindow;
			animations.back()->Load();
		}
		return animations.back();
	}

	void AssetManager::setWindow(Window* _window)
	{
		if (!noWindowLoad)
		{
			noWindowLoad = true;

			defaultWindow = _window;

			for (int i = 0; i < textures.size(); i++)
			{
				textures[i]->window = defaultWindow;
				textures[i]->Load();
			}

			for (int i = 0; i < animations.size(); i++)
			{
				animations[i]->window = defaultWindow;
				animations[i]->Load();
			}
		}
		else
		{
			defaultWindow = _window;
		}
	}
}