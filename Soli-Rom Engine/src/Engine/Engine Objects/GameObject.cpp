#include "precompiledheaders.h"
#include "GameObject.h"
#include "Engine/App.h"

namespace SoliRom
{
	std::vector<EngineObject*> EngineObject::objectList;

	EngineObject::EngineObject()
	{
		rect.w = 100;
		rect.h = 100;
		pos.x = rect.w / 2;
		pos.y = rect.h / 2;
		rect.x = pos.x - rect.w / 2;
		rect.y = pos.y - rect.h / 2;

		offset.x = 0;
		offset.y = 0;


		cam = nullptr;
		texture = nullptr;

		UpdateDrawRectToCam();

		id = objectList.size();
		objectList.push_back(this);
	}

	SDL_FPoint* EngineObject::GetPos()
	{
		return &pos;
	}

	void EngineObject::UpdatePos()
	{
		rect.x = pos.x + offset.x;
		rect.y = pos.y + offset.y;
	}

	SDL_FRect* EngineObject::GetRect()
	{
		return &rect;
	}

	void EngineObject::UpdateRect()
	{
		pos.x = rect.x - offset.x;
		pos.y = rect.y - offset.x;
	}

	SDL_FPoint* EngineObject::GetOffset()
	{
		return &offset;
	}

	void EngineObject::UpdateOffset()
	{
		rect.x = pos.x + offset.x;
		rect.y = pos.y + offset.y;
	}

	SDL_FRect* EngineObject::GetDrawRect()
	{
		return &drawRect;
	}

	void EngineObject::Draw()
	{
		if (texture != nullptr)
		{
			UpdateDrawRectToCam();
			SDL_RenderCopyF(texture->GetWindow()->getSDL_Renderer(), texture->Get(), NULL, &drawRect);
		}
		else
			DrawRect(true);
	}

	void EngineObject::Draw(SDL_RendererFlip _flip)
	{
		if (texture != nullptr)
		{
			UpdateDrawRectToCam();
			SDL_RenderCopyExF(texture->GetWindow()->getSDL_Renderer(), texture->Get(), NULL, &drawRect, NULL, NULL, _flip);
		}
		else
			DrawRect(true);
	}

	void EngineObject::DrawRect(bool defaultColor)
	{
		UpdateDrawRectToCam();

		if (defaultColor)
			SDL_SetRenderDrawColor(App::Get()->GetCurrentWindow()->getSDL_Renderer(), 255, 0, 0, 255);

		SDL_RenderDrawRectF(App::Get()->GetCurrentWindow()->getSDL_Renderer(), &drawRect);
		SDL_RenderDrawPointF(App::Get()->GetCurrentWindow()->getSDL_Renderer(), pos.x, pos.y);

		if (defaultColor)
			SDL_SetRenderDrawColor(App::Get()->GetCurrentWindow()->getSDL_Renderer(), 255, 255, 255, 255);
	}

	void EngineObject::SetTexture(Asset::Texture* _texture)
	{
		texture = _texture;
	}

	void EngineObject::SetCam(Camera* _cam)
	{
		cam = _cam;
	}

	void EngineObject::UpdateDrawRectToCam()
	{
		if (cam != nullptr)
		{
			drawRect = {
				(rect.x - cam->x) * cam->scale,
				(rect.y - cam->y) * cam->scale,
				rect.w * cam->scale,
				rect.h * cam->scale
			};
		}
		else
		{
			drawRect = rect;
		}
	}

	EngineObject::~EngineObject()
	{
		//erases from list
		objectList.erase(objectList.begin() + id);
		//remaps ids
		for (int i = id; i < objectList.size(); i++)
			objectList[i]->id--;
	}
}