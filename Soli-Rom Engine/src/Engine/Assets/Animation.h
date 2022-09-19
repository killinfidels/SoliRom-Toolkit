#pragma once
#include "Engine/Tools/Timer.h"

namespace SoliRom
{
	class AssetManager;
}

namespace SoliRom::Asset
{
	class Animation
	{
	private: //fucky change back to private when fix
		//animation file format should be "file_1.png"

		//format for animations should be "name_x" where x is the frame number

		//path to either first frame or txt file including all frames
		Animation(std::string _name, std::string _path);
		Animation(std::string _name, std::string _path, int _frameTime);

		void Init();
		bool Load();
	public:
		bool CreateTextFile();

		//plays the animation and returns current frame;
		Texture* Get();

		void Reset();
		void Start();
		void Skip();
		void Stop();
		//returns number of times animation has completed
		int Done();

		bool switchFrame(int _frame, std::string _path);
		bool switchFrame(int _frame, Texture* _texture);
		bool switchFrameTime(int _frame, int _frameTime);

	private:
		//path to first frame or .txt file
		std::string name = "NO ANIMATION";
		std::string path = "NO PATH";

		//frame array of textures
		std::vector<Texture*> frame;
		//milliseconds
		std::vector<int> frameTime;

		Window* window = NULL;

		Timer frameTimer;

		//flags
		int currentFrame = 0;
		int defaultFrameTime = 500;
		bool playing = false;
		bool finished = false;
		bool loaded = false;
		int loopCounter = 0;

	public:
		friend class ::SoliRom::AssetManager;
	};
}

