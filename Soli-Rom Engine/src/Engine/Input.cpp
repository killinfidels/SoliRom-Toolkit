#include "precompiledheaders.h"
#include "Input.h"
#include "Log.h"

namespace SoliRom
{
	MouseState EventHandler::mouse = {0, 0, IDLE};
	SDL_Event EventHandler::e;
	bool EventHandler::quit = false;

	void EventHandler::updateMouse()
	{
		//if clicked last update set to held
		if (mouse.mouseState == CLICKED)
		{
			mouse.mouseState = HELD;
		}

		while (SDL_PollEvent(&e) != 0)
		{
			switch (e.type)
			{
			case SDL_MOUSEMOTION:
				mouse.x = e.motion.x;
				mouse.y = e.motion.y;
				break;
			case SDL_MOUSEBUTTONDOWN:
				mouse.mouseState = CLICKED;
				SR_CORE_INFO("x: %i, y: %i", mouse.x, mouse.y);
				break;
			case SDL_MOUSEBUTTONUP:
				mouse.mouseState = IDLE;
				break;
			case SDL_QUIT:
				quit = true;
				break;
			default:
				break;
			}
		}
	}

	int EventHandler::getMouseX()
	{
		return mouse.x;
	}

	int EventHandler::getMouseY()
	{
		return mouse.y;
	}

	MouseCondition EventHandler::getMouseState()
	{
		return mouse.mouseState;
	}

	bool EventHandler::getQuit()
	{
		return quit;
	}

	bool EventHandler::mouseInObj(GameObject* _obj)
	{
		if (EventHandler::getMouseX() > _obj->scaled.x && EventHandler::getMouseX() < _obj->scaled.x + _obj->scaled.w)
		{
			if (EventHandler::getMouseY() > _obj->scaled.y && EventHandler::getMouseY() < _obj->scaled.y + _obj->scaled.h)
			{
				return true;
			}
		}

		return false;
	}
	bool EventHandler::click()
	{
		if (mouse.mouseState == CLICKED)
		{
			return true;
		}

		return false;
	}
}