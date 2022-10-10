#include "precompiledheaders.h"
#include "GameObject.h"
#include "Engine/App.h"

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

	SDL_Rect* GameObject::GetRect()
	{
		return &Rect;
	}

	void GameObject::Draw()
	{
		SDL_RenderCopy(texture->GetWindow()->getSDL_Renderer(), texture->Get(), NULL, &Rect);
	}

	void GameObject::SetTexture(Asset::Texture* _texture)
	{
		texture = _texture;
	}

	void GameObject::Draw(SDL_RendererFlip _flip)
	{
		if (texture != NULL)
		{
			SDL_RenderCopyEx(texture->GetWindow()->getSDL_Renderer(), texture->Get(), NULL, GetRect(), NULL, NULL, _flip);
		}
		else
		{
			DrawRect(true);
		}
	}

	void GameObject::DrawRect(bool defaultColor)
	{
		if (defaultColor)
			SDL_SetRenderDrawColor(App::Get()->GetCurrentWindow()->getSDL_Renderer(), 255, 0, 0, 255);

		SDL_RenderDrawRect(App::Get()->GetCurrentWindow()->getSDL_Renderer(), GetRect());

		if (defaultColor)
			SDL_SetRenderDrawColor(App::Get()->GetCurrentWindow()->getSDL_Renderer(), 255, 255, 255, 255);
	}

	//Move that amount left or right
	void GameObject::Move(int _x, int _y)
	{
		setPosition(GetRect()->x + _x, GetRect()->y + _y);
	}
}

