#pragma once
#include "Window.h"
#include "Asset.h"
#include "Layer.h"

namespace SoliRom
{
	class GameObject
	{
		SDL_Rect Rect;

		virtual int script();

		void setSize(int width, int height);
		void setPosition(int x, int y);

		bool visible = true;

		int assetsN;
		std::vector<Asset> Assets;
	};
}


