#pragma once
#include "Window.h"
#include "Asset.h"
#include "Layer.h"

namespace SoliRom
{
	class GameObject
	{
	public:
		//virtual int script();

		void setSize(int width, int height);
		void setPosition(int x, int y);

		bool visible = true;

		SDL_Rect* getRect();

	private:
		SDL_Rect Rect;
		int assetsN;
		std::vector<Asset> Assets;
	};
}


