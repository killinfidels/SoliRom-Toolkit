#pragma once

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
	};
}


