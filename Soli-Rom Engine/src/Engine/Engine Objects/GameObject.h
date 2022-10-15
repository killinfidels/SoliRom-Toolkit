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

		virtual void script() {};

		bool visible = true;
		bool useSript = true;

		//pos - if used to change value then call UpdatePos
		SDL_FPoint* GetPos();
		void UpdatePos();

		//World Rect - if used to change x,y then call UpdateRect
		SDL_FRect* GetRect();
		void UpdateRect();

		//Rect offset - if used to change value then call Update Offset
		SDL_FPoint* GetOffset();
		void UpdateOffset();

		//return draw rect - for clicking and such
		SDL_FRect* GetDrawRect();

		void Draw();
		void Draw(SDL_RendererFlip _flip);
		void DrawRect(bool defaultColor);

		void SetTexture(Asset::Texture* _texture);
		void SetCam(Camera* _cam);
	private:
		static std::vector<EngineObject*> objectList;
		int id;
	protected:
		void UpdateDrawRectToCam();
		Asset::Texture* texture;
		SDL_FPoint pos;
		SDL_FPoint offset;
		SDL_FRect rect;
		SDL_FRect drawRect;
		Camera* cam;
	};
}


