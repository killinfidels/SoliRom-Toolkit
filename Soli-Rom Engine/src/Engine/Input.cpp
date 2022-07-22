#include "precompiledheaders.h"
#include "Input.h"

namespace SoliRom
{
	MouseState EventHandler::mouse = {0, 0, IDLE};
	SDL_Event EventHandler::e;
	bool EventHandler::quit = false;

	void EventHandler::updateMouse()
	{
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
				break;
			case SDL_MOUSEBUTTONUP:
				mouse.mouseState = IDLE;
				break;
			case SDL_QUIT:
				quit = true;
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
}