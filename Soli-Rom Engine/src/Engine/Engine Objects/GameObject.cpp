#include "precompiledheaders.h"
#include "GameObject.h"

namespace SoliRom
{
	GameObject::GameObject()
	{
		Rect.x = 0;
		Rect.y = 0;
		Rect.w = 10;
		Rect.h = 10;

		assetsN = 0;
	}

	void GameObject::setSize(int width, int height)
	{
		Rect.w = width;
		Rect.h = height;
	}
	void GameObject::setPosition(int x, int y)
	{
		Rect.x = x;
		Rect.y = y;
	}
	SDL_Rect* GameObject::getRect()
	{
		return &Rect;
	}
}