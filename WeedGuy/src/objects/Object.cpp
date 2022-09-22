#include "../core.h"
#include "Object.h"

void Object::draw()
{
	CheckRender();

	if (texture != NULL)
	{
		SDL_RenderCopy(renderer, texture, NULL, GetRect());
	}
	else
	{
		drawRect(true);
	}
}

void Object::draw(SDL_RendererFlip _flip)
{
	CheckRender();

	if (texture != NULL)
	{
		SDL_RenderCopyEx(renderer, texture, NULL, GetRect(), NULL, NULL, _flip);
	}
	else
	{
		drawRect(true);
	}
}

void Object::drawRect(bool defaultColor)
{
	CheckRender();

	if (defaultColor)
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

	SDL_RenderDrawRect(renderer, GetRect());

	if (defaultColor)
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
}

//move that amount left or right
void Object::move(int _x, int _y)
{
	setPosition(GetRect()->x + _x, GetRect()->y + _y);
}

void Object::setTexture(SoliRom::Asset::Texture* _texture)
{
	texture = _texture->Get();
	renderer = _texture->GetWindow()->getSDL_Renderer();
}

void Object::CheckRender()
{
	if (renderer == NULL)
	{
		SoliRom::App::Get()->GetCurrentWindow()->getSDL_Renderer();
	}
}
