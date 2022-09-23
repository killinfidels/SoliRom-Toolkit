#pragma once
#include "Engine/Assets/Texture.h"
#include "Engine/Windows/Window.h"

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

		void Draw();

		void SetTexture(Asset::Texture* _texture);

	private:
		Asset::Texture* texture;
		SDL_Rect Rect;
		int assetsN;
	};
}


