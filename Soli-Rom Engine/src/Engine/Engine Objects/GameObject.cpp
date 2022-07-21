#include "precompiledheaders.h"
#include "GameObject.h"

namespace SoliRom
{
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