#pragma once
#include "Engine/Assets/Texture.h"
#include "Engine/Windows/Window.h"
#include "Camera.h"

namespace SoliRom
{
	class EngineObject
	{
	public:
		EngineObject();
		~EngineObject();

		//Moves pos certain amount
		void Move(float _x, float _y);

		//pos - if used to change value then call UpdatePos
		SDL_FPoint* GetPos();
		void UpdatePos();
		void SetPos(float _x, float _y);

		//World Rect - if used to change x,y then call UpdateRect
		SDL_FRect* GetRect();
		void UpdateRect();
		void SetRect(float _x, float _y, float _w, float _h);
		void SetRect(SDL_FRect _rect);
		void SetSize(float _w, float _h);

		//Rect offset - if used to change value then call Update Offset
		SDL_FPoint* GetOffset();
		void UpdateOffset();
		void SetOffset(float _x, float _y);

		//return draw rect - for clicking and such
		SDL_FRect* GetScreenRect();

		void Draw();
		void Draw(SDL_RendererFlip _flip);
		void DrawRect();

		void SetTexture(Asset::Texture* _texture);

		void SetCam(Camera* _cam);
	private:
		static std::vector<EngineObject*> objectList;
		int id;
	protected:
		void UpdateScreenPositions();
		Asset::Texture* texture;

		//texture rect
		SDL_FPoint pos;
		SDL_FPoint screenPos;
		SDL_FPoint offset;
		SDL_FRect rect;
		SDL_FRect screenRect;

		Camera* cam;
	};
}


