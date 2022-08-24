#pragma once

namespace SoliRom
{
	class GameObject
	{
	public:
		GameObject();

		//virtual int script();

		void setSize(int width, int height);
		void setPosition(int x, int y);

		bool visible = true;
		bool use = true;

		SDL_Rect* getRect();

		SDL_Rect scaled;
	private:
		SDL_Rect Rect;
		int assetsN;
	};
}


