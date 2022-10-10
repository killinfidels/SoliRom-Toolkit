#include "precompiledheaders.h"
#include "Engine/Windows/Window.h"
#include "Engine/Assets/Texture.h"
#include "Engine/Tools/Timer.h"
//#include "Engine/Assets/AssetManager.h"
#include "Engine/Log.h"
#include "Animation.h"

namespace SoliRom::Asset
{
	Animation::Animation(std::string _name, std::string _path, int _frameTime)
	{
		path = _path;
		name = _name;
		defaultFrameTime = _frameTime;

		Init();
	}

	Animation::Animation(std::string _name, std::string _path)
	{
		path = _path;
		name = _name;

		Init();
	}

	void Animation::Init()
	{
		//check if file exists
		if (SDL_RWFromFile(path.c_str(), "r") == NULL)
		{
			SR_CORE_WARN("Animation failed to load: %s. Error: %s", path.c_str(), SDL_GetError());
		}
		else
		{
			//load if text file
			if (path.find(".txt") != std::string::npos)
			{
				//load text file
			}

			//auto find frames from path to first if not text file
			//seperate frame number from path
			size_t pos = path.rfind("_");

			int frameNumber;
			//catches the error from stoi for not having a number in the string
			try
			{
				frameNumber = std::stoi(path.substr(pos + 1, path.rfind(".") - pos - 1));
			}
			catch (...)
			{
				frameNumber = 0;
			}

			if (pos == std::string::npos || frameNumber != 1)
			{
				SR_CORE_WARN("Animation path does not lead to first frame: '%s'.\nAnimations should be format like this: 'Animation_1.png', etc.", path.c_str());
			}
			else
			{
				std::string firstHalf = path.substr(0, pos + 1);
				std::string lastHalf = path.substr(path.rfind("."));

				name = firstHalf.substr(firstHalf.rfind("/") + 1, firstHalf.rfind("_") - firstHalf.rfind("/") - 1);

				int i = 1;

				//increment frame number and load as many frames as possible
				do
				{
					std::string framePath = firstHalf + std::to_string(i) + lastHalf;
					frame.resize(i);
					frameTime.resize(i);
					frame[i - 1] = new Texture(framePath.substr(framePath.rfind("/") + 1, framePath.rfind(".") - framePath.rfind("/") - 1), framePath, true);
					frameTime[i - 1] = defaultFrameTime;
					i++;
				} while (SDL_RWFromFile((firstHalf + std::to_string(i) + lastHalf).c_str(), "r") != NULL);

				SR_CORE_TRACE("Animation '%s' created with %i frames.", name.c_str(), i - 1);
			}
		}
	}

	bool Animation::Load()
	{
		if (window == NULL)
		{
			SR_CORE_WARN("Animation: '%' loading failed, no target window to render.\nPath: '%s'", name.c_str(), path.c_str());
			return loaded;
		}
		else
		{
			for (int i = 0; i < frame.size(); i++)
			{
				frame[i]->window = window;
				frame[i]->Load();
			}
		SR_CORE_TRACE("Animation '%s' loaded for Window: '%s'.", name.c_str(), window->getWindowName().c_str());

		loaded = true;
		}

		return loaded;
	}

	Texture* Animation::Get()
	{
		if (frame.size() == 0)
		{
			SR_CORE_WARN("No animation to play!");

			return NULL;
		}
		else
		{
			frameTimer.update();

			finished = false;

			if (frameTimer.checkElapsed(frameTime[currentFrame]))
			{
				currentFrame++;
				if (currentFrame >= frame.size())
				{
					finished = true;
					loopCounter++;
					currentFrame = 0;
				}

				frameTimer.Reset();
			}

		}

		return frame[currentFrame];
	}

	void Animation::Reset()
	{
		frameTimer.Reset();

		currentFrame = 0;

		loopCounter = 0;

		finished = false;
	}

	void Animation::Start()
	{
		frameTimer.Start();
		playing = true;
	}

	void Animation::Skip()
	{
		frameTimer.Reset();
		currentFrame++;
		if (currentFrame >= frame.size())
			currentFrame = 0;
	}

	void Animation::Stop()
	{
		frameTimer.Stop();
		playing = false;
	}

	int Animation::Done()
	{
		return finished;
	}
}