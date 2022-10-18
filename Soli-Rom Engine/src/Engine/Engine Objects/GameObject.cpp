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

		UpdateScreenPositions();

		id = objectList.size();
		objectList.push_back(this);
	}

	void EngineObject::Move(float _x, float _y)
	{
		pos.x += _x;
		pos.y += _y;

		UpdatePos();
	}

	SDL_FPoint* EngineObject::GetPos()
	{
		return &pos;
	}

	void EngineObject::UpdatePos()
	{
		rect.x = pos.x + offset.x;
		rect.y = pos.y + offset.y;

		UpdateScreenPositions();
	}

	void EngineObject::SetPos(float _x, float _y)
	{
		pos.x = _x;
		pos.y = _y;

		UpdatePos();
	}

	SDL_FRect* EngineObject::GetRect()
	{
		return &rect;
	}

	void EngineObject::UpdateRect()
	{
		pos.x = rect.x - offset.x;
		pos.y = rect.y - offset.x;

		UpdateScreenPositions();
	}

	void EngineObject::SetRect(float _x, float _y, float _w, float _h)
	{
		rect = { _x,_y,_w,_h };
		UpdateRect();
	}

	void EngineObject::SetRect(SDL_FRect _rect)
	{
		rect = _rect;
		UpdateRect();
	}

	void EngineObject::SetSize(float _w, float _h)
	{
		rect.w = _w;
		rect.h = _h;
	}

	SDL_FPoint* EngineObject::GetOffset()
	{
		return &offset;
	}

	void EngineObject::UpdateOffset()
	{
		rect.x = pos.x + offset.x;
		rect.y = pos.y + offset.y;

		UpdateScreenPositions();
	}

	void EngineObject::SetOffset(float _x, float _y)
	{
		offset = { _x, _y };
		UpdateOffset();
	}

	SDL_FRect* EngineObject::GetScreenRect()
	{
		return &screenRect;
	}

	void EngineObject::Draw()
	{
		if (texture != nullptr)
		{
			UpdateScreenPositions();
			SDL_RenderCopyF(texture->GetWindow()->getSDL_Renderer(), texture->Get(), NULL, &screenRect);
		}
		else
			DrawRect();
	}

	void EngineObject::Draw(SDL_RendererFlip _flip)
	{
		if (texture != nullptr)
		{
			UpdateScreenPositions();
			SDL_RenderCopyExF(texture->GetWindow()->getSDL_Renderer(), texture->Get(), NULL, &screenRect, NULL, NULL, _flip);
		}
		else
			DrawRect();
	}

	void EngineObject::DrawRect()
	{
		UpdateScreenPositions();

		SDL_SetRenderDrawColor(App::Get()->GetCurrentWindow()->getSDL_Renderer(), 255, 0, 0, 255);
		SDL_RenderDrawRectF(App::Get()->GetCurrentWindow()->getSDL_Renderer(), &screenRect);

		SDL_SetRenderDrawColor(App::Get()->GetCurrentWindow()->getSDL_Renderer(), 0, 0, 255, 255);
		SDL_RenderDrawPointF(App::Get()->GetCurrentWindow()->getSDL_Renderer(), screenPos.x, screenPos.y);

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

	void EngineObject::UpdateScreenPositions()
	{
		if (cam != nullptr)
		{
			screenRect = {
				(rect.x - cam->x) * cam->scale,
				(rect.y - cam->y) * cam->scale,
				rect.w * cam->scale,
				rect.h * cam->scale
			};

			screenPos = {
				(pos.x - cam->x) * cam->scale,
				(pos.y - cam->y) * cam->scale,
			};
		}
		else
		{
			screenRect = rect;
			screenPos = pos;
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