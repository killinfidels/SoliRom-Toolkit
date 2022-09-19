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

		SDL_Rect* GetRect();

		int sizeMul;
	private:
		SDL_Rect Rect;
		int assetsN;
	};
}


